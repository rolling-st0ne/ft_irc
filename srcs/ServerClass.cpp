/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:58:30 by casteria          #+#    #+#             */
/*   Updated: 2020/12/15 20:00:58 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "ServerClass.hpp"
#include <stdlib.h>

// __CONSTRUCTORS
Server::Server()
{
}

Server::Server(const Server &other)
{
	(void)other;
}

Server::Server(const int& port, const std::string& password) // creation of server
	:	password(password)
{
	uplink = 0;
	create_server(port, password);
}

Server::Server(const char *another_server, const int& port, const std::string& password)
{
	this->password = password;
	create_server(port, password);
	const std::string glued_params(another_server);
	std::vector<std::string> params = strsplit(glued_params, ':');
	if (params.size() != 3)
		throw ServerException("Bad arguments");
	std::string target_host = params[0];
	int target_port = atoi(params[1].c_str());
	if (target_port < 1024 || target_port > 65535)
		throw ServerException("Bad target port");
	std::string target_pass = params[2];
	std::cerr << "Connecting to " << target_host << ":" << target_port << " (" << target_pass << ")\n";
	connect_server(target_host, params[1], target_pass);
}

// __DESTRUCTOR
Server::~Server()
{
}

// __OPERATORS
Server &Server::operator=(const Server &other)
{
	(void)other;
	return (*this);
}

// __FUNCTIONS

void	Server::connect_server(const std::string& host, const std::string& port, const std::string pass)
{
	struct addrinfo *result;
	sockaddr_in		connect_info;

	connect_info.sin_addr.s_addr = htonl(INADDR_ANY);
	connect_info.sin_family = AF_INET;
	connect_info.sin_port = htons(atoi(port.c_str()));

	if (getaddrinfo(host.c_str(), port.c_str(), NULL, &result))
		throw ServerException(errno);
	while (result->ai_next)
		result = result->ai_next;
	uplink = socket(AF_INET, SOCK_STREAM, 0);
	if (uplink < 0)
		throw ServerException(errno);
	if (connect(uplink, (sockaddr *)&connect_info, sizeof(sockaddr_in)) < 0)
		throw ServerException(errno);
	freeaddrinfo(result);
	
	Client new_server;
	new_server.sock.socket_fd = uplink;
	new_server.status = WAITING_FOR_CONNECTION;
	addClient(new_server);
	fcntl(uplink, F_SETFL, O_NONBLOCK);
	std::string start = "PASS " + pass + " 0210 IRC|\r\n";
	start += "SERVER " + this->name + " 1 info\r\n";
	send(uplink, start.c_str(), start.size(), 0);
}

void	Server::create_server(const int& port, const std::string& password)
{
	int					option = 1;

	timeout.tv_sec = 1;
	this->password = password;
	sock.socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock.socket_fd == FAIL)
		throw ServerException(errno);
	sock.addr.sin_family = AF_INET;
	sock.addr.sin_addr.s_addr = htonl(INADDR_ANY);
	sock.addr.sin_port = htons(port);
	setsockopt(sock.socket_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	if (bind(sock.socket_fd, (struct sockaddr *)&sock.addr, sizeof(sockaddr)) == FAIL)
		throw ServerException(errno);
	if (listen(sock.socket_fd, QUEUE_LEN_MAX) == FAIL)
		throw ServerException(errno);
	addHost(Host(getHostName(sock.addr), 0, "mb add some info later"));
	this->name = getHostName(sock.addr);
	std::ostringstream	os;
	os << "0.0.0.0/" << port;
	name = os.str();
}

void	Server::start()
{
	server_loop();
}

void	Server::server_loop()
{
	while (SERVER_RUNS)
	{
		fd_set readfds, writefds;
		int max_d = this->sock.socket_fd;
		int	select_result;

		initFds(max_d, readfds, writefds);
		timeval timeout = this->timeout;
		select_result = select(max_d + 1, &readfds, &writefds, NULL, &timeout);
#ifdef DEBUG_MODE
		//if (select_result == 0)
		//	DEBUG_MES("TIMEOUT. Clients: " << clients.size() << ", Users: " << users.size() << '\n')
#endif
		if (select_result < 0)
			throw ServerException(errno); // need signal handle (errno: EINTR)
		if (FD_ISSET(sock.socket_fd, &readfds))
			acceptNewClient();
		processClients(readfds, writefds);
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
	}
}

void							Server::initFds(int& max_d, fd_set& readfds, fd_set& writefds)
{
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_SET(this->sock.socket_fd, &readfds);
	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		FD_SET(it->sock.socket_fd, &readfds);
		if (!it->response.empty())
			FD_SET(it->sock.socket_fd, &writefds);
		if (it->sock.socket_fd > max_d)
			max_d = it->sock.socket_fd;
	}
}

void							Server::acceptNewClient()
{
	Client						new_client;

	new_client.sock.socket_fd = accept(sock.socket_fd, (sockaddr *)&new_client.sock.addr, &new_client.sock.socklen);
	if (new_client.sock.socket_fd < 0)
		throw ServerException(errno);
	fcntl(new_client.sock.socket_fd, F_SETFL, O_NONBLOCK);
	new_client.name = getHostName(new_client.sock.addr);
	addClient(new_client);
}

void							Server::processClients(fd_set &readfds, fd_set &writefds)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (FD_ISSET(clients[i].sock.socket_fd, &readfds))
		{
			processClientRequest(clients[i]);
		}
		if (clients[i].sock.socket_fd == -1)
		{
			std::cerr << "Found closed descriptor\n";
			rmClient(clients[i]);
			break;
		}
	}
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (FD_ISSET(clients[i].sock.socket_fd, &writefds))
			sendDataToClient(clients[i]);
	}
}

void							Server::processClientRequest(Client& client)
{
	char		buffer[BUFFER_SIZE];
	int			recv_ret;
	std::string	received_message;

	bzero(buffer, BUFFER_SIZE);
	recv_ret = recv(client.sock.socket_fd, buffer, BUFFER_SIZE, 0);
	if (recv_ret < 0)
		throw ServerException(errno);
	else if (recv_ret == 0)
	{
		std::string message = IrcAPI::user_by_nick(*this, client.name) + " QUIT " + "Disconnected";
		for (size_t i = 0; i < users.size(); i++)
		{
			if (users[i].nickname != client.name)
				IrcAPI::sendToUser(*this, users[i].nickname, message);
		}
		for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); it++)
		{
			for (size_t i = 0; i < it->members.size(); i++)
			{
				if (it->members[i] == client.name)
				{
					it->removeUser(client.name);
					break;
				}
			}
			if (it->members.size() == 0)
			{
				channels.erase(it);
				break;
			}
		}
		for (std::vector<User>::iterator it = users.begin(); it != users.end(); it++)
		{
			if (it->nickname == client.name)
			{
				users.erase(it);
				break;
			}
		}
		close(client.sock.socket_fd);
		rmClient(client);
	}
#ifdef DEBUG_MODE
	DEBUG_MES(client.sock.socket_fd << " SAYS: " << buffer)
#endif
	IrcAPI::run_query(*this, client, buffer);
}

void							Server::sendDataToClient(Client& client)
{
	std::string		response = client.response;
	send(client.sock.socket_fd, response.c_str(), response.size(), 0);
	client.response.clear();
}

void							Server::addClient(Client client)
{
	clients.push_back(client);
}

void							Server::addHost(Host host)
{
	hosts.push_back(host);
}

void							Server::rmClient(Client client) // to finalize;
{
	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->sock.socket_fd == client.sock.socket_fd)
		{
			clients.erase(it);
			break;
		}
	}
}

void							Server::propagate(const std::string& message, const std::string& source)
{
	for (size_t i = 0; i < connected_servers.size(); i++)
	{
		if (connected_servers[i] == source)
			continue;
		std::vector<Client>::iterator ite = clients.end();
		for (std::vector<Client>::iterator it = clients.begin(); it != ite; it++)
		{
			if (it->name == connected_servers[i])
			{
				it->response += message + "\r\n";
				std::cerr << "Propagating to " + connected_servers[i] << std::endl;
				break;
			}
		}
	}
}
