/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:14:48 by casteria          #+#    #+#             */
/*   Updated: 2020/11/20 00:27:15 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

static socket_info		createSocket(const char *port)
{
	int					socket_fd;
	struct sockaddr_in	address;
	socket_info			sock;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == FAIL)
		throw IrcException(errno);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(atoi(port));
	if (bind(socket_fd, (struct sockaddr *)&address, sizeof(sockaddr)) == FAIL)
		throw IrcException(errno);
	if (listen(socket_fd, QUEUE_LEN_MAX) == FAIL)
		throw IrcException(errno);
	sock.socket_fd = socket_fd;
	sock.addr = address;
	return (sock);
}

void					createOwnNetwork(char **argv, Server &serv)
{
	serv.setSocket(createSocket(argv[2]));
	serv.start();
}

void					joinNetwork(char **argv, Server &serv)
{
	serv.setSocket(createSocket(argv[1]));
	serv.start();
	(void)serv;
	(void)argv;
}