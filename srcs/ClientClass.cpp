/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:18:00 by casteria          #+#    #+#             */
/*   Updated: 2020/11/28 15:40:23 by casteria         ###   ########.fr       */
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
}

void		Client::Buffer::clear()
{
	this->response.clear();
}

bool		Client::Buffer::isEmpty() const
{
	return (response.empty());
}
