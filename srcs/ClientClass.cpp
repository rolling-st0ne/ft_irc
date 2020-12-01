/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:18:00 by casteria          #+#    #+#             */
/*   Updated: 2020/12/01 03:52:55 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

Client::Client()
{
}

Client::Client(const Client& other)
	:	sock(other.sock),
		buffer(other.buffer)
{
}

Client::~Client()
{
//	close(this->sock.socket_fd);
}

void		Client::Buffer::clear()
{
	this->response.clear();
}

bool		Client::Buffer::isEmpty() const
{
	return (response.empty());
}
