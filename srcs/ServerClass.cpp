/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:58:30 by casteria          #+#    #+#             */
/*   Updated: 2020/11/18 16:11:39 by casteria         ###   ########.fr       */
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
	while (true)
	{
		
	}
}