/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:14:48 by casteria          #+#    #+#             */
/*   Updated: 2020/11/17 17:33:59 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

static socket_info		createSocket(const char *port)
{
	int					socket_fd;
	struct sockaddr_in	adress;
	socket_info			sock;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == FAIL)
		throw SocketCreateFailedException();
	adress.sin_family = AF_INET;
	adress.sin_addr.s_addr = htonl(INADDR_ANY);
	adress.sin_port = htons(atoi(port));
	if (bind(socket_fd, (struct sockaddr *)&adress, sizeof(sockaddr)) == FAIL)
		throw BadSockAddrException();
	if (listen(socket_fd, QUEUE_LEN_MAX) == FAIL)
		throw ListenException();
	sock.socket_fd = socket_fd;
	sock.addr = adress;
	return (sock);
}

void					createOwnNetwork(char **argv, Server &serv)
{
	sockaddr_in		new_connection;
	socklen_t	new_connetion_socklen;

	serv.setSocket(createSocket(argv[2]));
	accept(serv.getSocket().socket_fd, (sockaddr *)&new_connection, &new_connetion_socklen);
	std::cout << "Signal accepted!" << std::endl;
	(void)serv;
	(void)argv;
}

void					joinNetwork(char **argv, Server &serv)
{
	serv.setSocket(createSocket(argv[1]));
	(void)serv;
	(void)argv;
}