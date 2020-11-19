/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:58:30 by casteria          #+#    #+#             */
/*   Updated: 2020/11/20 00:33:00 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerClass.hpp"


// __CONSTRUCTORS
Server::Server()
{
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
	while (true)
	{
		fd_set readfds, writefds;
		int max_d = this->socket.socket_fd;
		int	select_result;

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
		timeval timeout;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		select_result = select(max_d + 1, &readfds, &writefds, NULL, &timeout);
		if (select_result == 0) // time out
			continue ;
		if (select_result < 0)
		{
			std::cout << select_result << std::endl;
			throw IrcException(errno); // need signal handle (errno: EINTR)
		}
		if (FD_ISSET(socket.socket_fd, &readfds)) // if a new client tries to connect to server
		{
			socket_info		new_client;

			accept(socket.socket_fd, (sockaddr *)&new_client.addr, &new_client.socklen);
			std::cout << "Signal accepted!" << std::endl;
			int flags = fcntl(new_client.socket_fd, F_GETFL);
			fcntl(new_client.socket_fd, F_SETFL, flags | O_NONBLOCK);
			clients.push_back(new_client);
		}
		size_t i = 0;
		for (std::vector<socket_info>::const_iterator it = clients.begin(); it != clients.end(); it++)
		{
			std::cout << i++ << std::endl;
			if (FD_ISSET(it->socket_fd, &readfds))
				std::cout << "Received data from the client" << std::endl;
			if (FD_ISSET(it->socket_fd, &writefds))
				std::cout << "Sent data to the client" << std::endl;
		}
	}
}

const std::vector<socket_info>	&Server::getClients() const
{
	return (this->clients);
}

void							Server::addClient(socket_info &client)
{
	clients.push_back(client);
}