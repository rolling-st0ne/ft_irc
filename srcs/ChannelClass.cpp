/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelClass.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:45:07 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/12 05:17:48 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelClass.hpp"

Channel::Channel(std::string name, std::string creator)
	: name(name), creator(creator)
{
	members.push_back(creator);
	operators.push_back(creator);
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

void	Channel::addOperator(std::string oper)
{
	for (std::vector<std::string>::iterator it = operators.begin(); it != operators.end(); it++)
	{
		if (*it == oper)
			return;
	}
	operators.push_back(oper);
}

void	Channel::removeUser(std::string user)
{
	for (std::vector<std::string>::iterator it = members.begin(); it != members.end(); it++)
	{
		if (*it == user)
		{
			members.erase(it);
			removeOperator(user);
			return;
		}
	}
}

void	Channel::removeOperator(std::string oper)
{
	for (std::vector<std::string>::iterator it = operators.begin(); it != operators.end(); it++)
	{
		if (*it == oper)
		{
			operators.erase(it);
			break;
		}
	}
	if (operators.size() == 0 && members.size() > 0)
	{
		//operators.push_back(members[0]);
		// notify others about op change?
	}
}

bool	Channel::isUser(std::string user)
{
	for (std::vector<std::string>::iterator it = members.begin(); it != members.end(); it++)
	{
		if (*it == user)
			return true;
	}
	return false;
}

bool	Channel::isOperator(std::string user)
{
	for (std::vector<std::string>::iterator it = operators.begin(); it != operators.end(); it++)
	{
		if (*it == user)
			return true;
	}
	return false;
}