/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelClass.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:45:07 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/03 08:59:15 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelClass.hpp"

Channel::Channel(std::string name, std::string creator)
	: name(name), creator(creator)
{
	members.push_back(creator);
	std::cerr << "Channel " << name << " created by " << creator << std::endl;
}

bool	Channel::addUser(std::string user)
{
	for (std::vector<std::string>::iterator it = members.begin(); it != members.end(); it++)
	{
		if (*it == user)
			return false;
	}
	members.push_back(user);
	return true;
}

void	Channel::removeUser(std::string user)
{
	for (std::vector<std::string>::iterator it = members.begin(); it != members.end(); it++)
	{
		if (*it == user)
		{
			members.erase(it);
			return;
		}
	}
}