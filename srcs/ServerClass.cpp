/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:58:30 by casteria          #+#    #+#             */
/*   Updated: 2020/11/22 01:25:44 by casteria         ###   ########.fr       */
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
	for (std::vector<Client>::const_iterator it = clients.begin(); it != clients.end(); it++)
	{
		FD_SET(it->socket.socket_fd, &readfds);
	//	FD_SET(it->socket_fd, &writefds); // to add later
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
	for (std::vector<Client>::const_iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (FD_ISSET(it->socket.socket_fd, &readfds))
			processClientRequest(it->socket.socket_fd);
		if (FD_ISSET(it->socket.socket_fd, &writefds))
			sendDataToClient(it->socket.socket_fd);
	}
}

void							Server::processClientRequest(const int &socket_fd)
{
	char		buffer[BUFFER_SIZE];
	int			recv_length;
	t_message	received_message;

	recv_length = recv(socket_fd, buffer, BUFFER_SIZE, 0);
	if (recv_length < 0)
		throw IrcException(errno);
	received_message = parseRequest(buffer);
	std::cout << buffer;
	bzero(buffer, BUFFER_SIZE);
}

t_message							Server::parseRequest(const char *buffer)
{
	t_message			result;
	std::istringstream	strstream(buffer);
	strstream >> result.command;
	strstream >> result.content;

	return (result);
}

void							Server::sendDataToClient(const int &socket_fd)
{
//	char buffer[BUFFER_SIZE];
	(void)socket_fd;
//	strcpy(buffer, "Hello from server!");
//	std::cout << "Sent data to the client" << std::endl;
//	send(socket_fd, buffer, 20, 0);
}

const std::vector<Client>		&Server::getClients() const
{
	return (this->clients);
}

void							Server::addClient(Client &client)
{
	clients.push_back(client);
}