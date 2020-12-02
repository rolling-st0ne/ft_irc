/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:58:30 by casteria          #+#    #+#             */
/*   Updated: 2020/12/02 21:59:31 by gwynton          ###   ########.fr       */
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
	create_server(port, password);
}

Server::Server(const char *another_server, const int& port, const std::string& password)
{
	create_server(port, password);
	(void)another_server;
	// . . .
	// here will be implemented connection to host (other server)
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

void	Server::create_server(const int& port, const std::string& password)
{
	int					option = 1;

	timeout.tv_sec = 2;
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
	//new_client.name = "<unknown>";
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
		rmClient(client);
#ifdef DEBUG_MODE
	DEBUG_MES("SOMEONE SAYS: " << buffer)
#endif
	IrcAPI::run_query(*this, client, buffer);
	//std::cerr << clients.size() << ' ' << users.size() << std::endl;
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
	for (size_t i = 0; i < clients.size(); i++)
		std::cerr << "Client " << i << ": " << clients[i].name << std::endl;
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
