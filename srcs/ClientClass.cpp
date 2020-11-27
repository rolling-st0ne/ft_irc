/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:18:00 by casteria          #+#    #+#             */
/*   Updated: 2020/11/27 20:08:42 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

Client::Client()
{
}

Client::~Client()
{
}

void		Client::Buffer::clear()
{
	this->received.command.clear();
	this->received.content.clear();
	this->response.clear();
}

bool		Client::Buffer::isEmpty() const
{
	return (response.empty());
}
