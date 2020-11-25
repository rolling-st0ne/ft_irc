/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:58:30 by casteria          #+#    #+#             */
/*   Updated: 2020/11/25 20:27:30 by casteria         ###   ########.fr       */
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

Server::Server(const int& host_port, const std::string& host_password, const int& port, const std::string& password)
{
	create_server(port, password);
	(void)host_port;
	(void)host_password;
	// . . .
	// here will be implemented connection to host (ohter server)
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

	timeout.tv_sec = 5;
	this->password = password;
	server_socket.socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket.socket_fd == FAIL)
		throw IrcException(errno);
	server_socket.addr.sin_family = AF_INET;
	server_socket.addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_socket.addr.sin_port = htons(port);
	setsockopt(server_socket.socket_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	if (bind(server_socket.socket_fd, (struct sockaddr *)&server_socket.addr, sizeof(sockaddr)) == FAIL)
		throw IrcException(errno);
	if (listen(server_socket.socket_fd, QUEUE_LEN_MAX) == FAIL)
		throw IrcException(errno);
}

void	Server::setSocket(socket_info socket)
{
	this->server_socket.socket_fd = socket.socket_fd;
	this->server_socket.addr = socket.addr;
}

socket_info Server::getSocket() const
{
	return (this->server_socket);
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
		int max_d = this->server_socket.socket_fd;
		int	select_result;

		initFds(max_d, readfds, writefds);
		timeval timeout = this->timeout;
		select_result = select(max_d + 1, &readfds, &writefds, NULL, &timeout);
#ifdef DEBUG_MODE
		if (select_result == 0)
			DEBUG_MES("TIMEOUT\n")
#endif
		else if (select_result < 0)
			throw IrcException(errno); // need signal handle (errno: EINTR)
		if (FD_ISSET(server_socket.socket_fd, &readfds))
			acceptNewClient();
		processClients(readfds, writefds);
		FD_ZERO(&readfds); FD_ZERO(&writefds);
	}
}

void							Server::initFds(int& max_d, fd_set& readfds, fd_set& writefds)
{
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_SET(this->server_socket.socket_fd, &readfds);
	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		FD_SET(it->sock.socket_fd, &readfds);
		if (!it->buffer.isEmpty())
			FD_SET(it->sock.socket_fd, &writefds);
		if (it->sock.socket_fd > max_d)
			max_d = it->sock.socket_fd;
	}
}

void							Server::acceptNewClient()
{
	Client						new_client;

	new_client.sock.socket_fd = accept(server_socket.socket_fd, (sockaddr *)&new_client.sock.addr, &new_client.sock.socklen);
	if (new_client.sock.socket_fd < 0)
		throw IrcException(errno);
	//int flags = fcntl(new_client.socket.socket_fd, F_GETFL); 			// i don't quite understand what it is for
	fcntl(new_client.sock.socket_fd, F_SETFL, O_NONBLOCK);	// 
	addClient(new_client);
}

void							Server::processClients(fd_set &readfds, fd_set &writefds)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (FD_ISSET(clients[i].sock.socket_fd, &readfds))
		{
			processClientRequest(clients[i]);
			FD_CLR(clients[i].sock.socket_fd, &readfds);
		}
		if (FD_ISSET(clients[i].sock.socket_fd, &writefds))
			sendDataToClient(clients[i]);
	}
}

void							Server::processClientRequest(Client &client)
{
	char		buffer[BUFFER_SIZE];
	int			recv_ret;
	std::string	received_message;

	bzero(buffer, BUFFER_SIZE);
	recv_ret = recv(client.sock.socket_fd, buffer, BUFFER_SIZE, 0);
	if (recv_ret < 0)
		throw IrcException(errno);
	else if (recv_ret == 0)
		rmClient(client);
#ifdef DEBUG_MODE
	DEBUG_MES("SOMEONE SAYS: " << buffer)
#endif
#ifdef DEBUG_MODE
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].sock.socket_fd != client.sock.socket_fd && clients[i].sock.socket_fd != server_socket.socket_fd)
			clients[i].buffer.response = std::string(buffer);
	}
#endif
	IrcAPI::run_query(buffer);
}

void							Server::sendDataToClient(Client &client)
{
	std::string		response = client.buffer.response;
	send(client.sock.socket_fd, response.c_str(), response.size(), 0);
	client.buffer.clear();
}

const std::vector<Client>		&Server::getClients() const
{
	return (this->clients);
}

void							Server::addClient(Client &client)
{
	clients.push_back(client);
}

void							Server::rmClient(Client &client)
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