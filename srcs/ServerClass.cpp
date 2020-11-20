/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:58:30 by casteria          #+#    #+#             */
/*   Updated: 2020/11/20 14:53:24 by casteria         ###   ########.fr       */
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

// __FUCNTIONS
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
		select_result = select(max_d + 1, &readfds, &writefds, NULL, &this->timeout);
		if (select_result == 0); // time out
		else if (select_result < 0)
			throw IrcException(errno); // need signal handle (errno: EINTR)
		if (FD_ISSET(socket.socket_fd, &readfds))
			acceptNewClient();
		processClients(readfds, writefds);
	}
}

void							Server::initFds(int& max_d, fd_set& readfds, fd_set& writefds)
{
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_SET(this->socket.socket_fd, &readfds);
	for (std::vector<socket_info>::const_iterator it = clients.begin(); it != clients.end(); it++)
	{
		FD_SET(it->socket_fd, &readfds);
		FD_SET(it->socket_fd, &writefds);
		if (it->socket_fd > max_d)
			max_d = it->socket_fd;
	}
}

void							Server::acceptNewClient()
{
	socket_info		new_client;

	new_client.socket_fd = accept(socket.socket_fd, (sockaddr *)&new_client.addr, &new_client.socklen);
	if (new_client.socket_fd < 0)
		throw IrcException(errno);
	int flags = fcntl(new_client.socket_fd, F_GETFL);
	fcntl(new_client.socket_fd, F_SETFL, flags | O_NONBLOCK);
	std::cout << clients.size() << std::endl;
	addClient(new_client);
	std::cout << clients.size() << std::endl;
}

void							Server::processClients(fd_set &readfds, fd_set &writefds)
{
	for (std::vector<socket_info>::const_iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (FD_ISSET(it->socket_fd, &readfds))
			receiveDataFromClient();
		if (FD_ISSET(it->socket_fd, &writefds))
			sendDataToClient();
	}
}

void							Server::receiveDataFromClient()
{
	std::cout << "Received data from the client" << std::endl;
}

void							Server::sendDataToClient()
{
	std::cout << "Sent data to the client" << std::endl;
}

const std::vector<socket_info>	&Server::getClients() const
{
	return (this->clients);
}

void							Server::addClient(socket_info client)
{
	clients.push_back(client);
}