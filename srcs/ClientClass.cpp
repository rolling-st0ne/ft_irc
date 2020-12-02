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
		name(other.name)
{
}

Client::~Client()
{
//	close(this->sock.socket_fd);
}
