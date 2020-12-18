/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:18:00 by casteria          #+#    #+#             */
/*   Updated: 2020/12/18 02:27:45 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

Client::Client()
{
	status = CLIENT;
	ssl_connected = false;
}

Client::Client(const Client& other) // MB
	:	sock(other.sock),
		name(other.name),
		password(other.password),
		status(other.status),
		ssl_connected(other.ssl_connected),
		response(other.response)
{
}

Client::~Client()
{
//	close(this->sock.socket_fd);
//	SSL_free(this->ssl);
}
