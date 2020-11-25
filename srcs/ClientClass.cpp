/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:18:00 by casteria          #+#    #+#             */
/*   Updated: 2020/11/25 21:58:52 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

Client::Client()
	:	authenticated(false),
		nickname(),
		status(UNKNOWN)
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
