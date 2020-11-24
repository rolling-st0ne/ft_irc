/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:58:30 by casteria          #+#    #+#             */
/*   Updated: 2020/11/24 22:45:41 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerClass.hpp"


// __CONSTRUCTORS
Server::Server()
{
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
}

Server::Server(const Server &other)
{
	(void)other;
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
void	Server::setSocket(socket_info socket)
{
	this->socket.socket_fd = socket.socket_fd;
	this->socket.addr = socket.addr;
}

socket_info Server::getSocket() const
{
	return (this->socket);
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
		int max_d = this->socket.socket_fd;
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
		if (FD_ISSET(socket.socket_fd, &readfds))
			acceptNewClient();
		processClients(readfds, writefds);
		processClients(readfds, writefds);
		FD_ZERO(&readfds); FD_ZERO(&writefds);
	}
}

void							Server::initFds(int& max_d, fd_set& readfds, fd_set& writefds)
{
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_SET(this->socket.socket_fd, &readfds);
	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		FD_SET(it->socket.socket_fd, &readfds);
		if (!it->buffer.isEmpty())
			FD_SET(it->socket.socket_fd, &writefds);
		if (it->socket.socket_fd > max_d)
			max_d = it->socket.socket_fd;
	}
}

void							Server::acceptNewClient()
{
	Client						new_client;

	new_client.socket.socket_fd = accept(socket.socket_fd, (sockaddr *)&new_client.socket.addr, &new_client.socket.socklen);
	if (new_client.socket.socket_fd < 0)
		throw IrcException(errno);
	int flags = fcntl(new_client.socket.socket_fd, F_GETFL); 			// i don't quite understand what it is for
	fcntl(new_client.socket.socket_fd, F_SETFL, flags | O_NONBLOCK);	// 
	addClient(new_client);
}

void							Server::processClients(fd_set &readfds, fd_set &writefds)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (FD_ISSET(clients[i].socket.socket_fd, &readfds))
			processClientRequest(clients[i]);
		if (FD_ISSET(clients[i].socket.socket_fd, &writefds))
			sendDataToClient(clients[i]);
	}
}

void							Server::processClientRequest(Client &client)
{
	char		buffer[BUFFER_SIZE];
	int			recv_ret;
	std::string	received_message;

	bzero(buffer, BUFFER_SIZE);
	recv_ret = recv(client.socket.socket_fd, buffer, BUFFER_SIZE, 0);
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
		if (clients[i].socket.socket_fd != client.socket.socket_fd && clients[i].socket.socket_fd != socket.socket_fd)
			clients[i].buffer.response = std::string(buffer);
	}
#endif
	IrcAPI::run_query(buffer);
	bzero(buffer, BUFFER_SIZE);
}

void							Server::sendDataToClient(Client &client)
{
	std::string		response = client.buffer.response;
	send(client.socket.socket_fd, response.c_str(), response.size(), 0);
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
		if (it->socket.socket_fd == client.socket.socket_fd)
		{
			clients.erase(it);
			break;
		}
	}
}