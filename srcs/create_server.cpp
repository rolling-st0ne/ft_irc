/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:14:48 by casteria          #+#    #+#             */
/*   Updated: 2020/11/19 12:52:06 by casteria         ###   ########.fr       */
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
		throw IrcException(errno);
	adress.sin_family = AF_INET;
	adress.sin_addr.s_addr = htonl(INADDR_ANY);
	adress.sin_port = htons(atoi(port));
	if (bind(socket_fd, (struct sockaddr *)&adress, sizeof(sockaddr)) == FAIL)
		throw IrcException(errno);
	if (listen(socket_fd, QUEUE_LEN_MAX) == FAIL)
		throw IrcException(errno);
	sock.socket_fd = socket_fd;
	sock.addr = adress;
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