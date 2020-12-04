/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:10:11 by casteria          #+#    #+#             */
/*   Updated: 2020/12/04 04:34:50 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

bool		IrcAPI::nick_in_use(Server& server, const std::string& nickname)
{
	for (std::vector<User>::iterator it = server.users.begin(); it != server.users.end(); it++)
	{
		if (it->nickname == nickname)
			return (true);
	}
	return (false);
}

std::string	IrcAPI::user_by_nick(Server& server, const std::string& nickname)
{
	for (std::vector<User>::iterator it = server.users.begin(); it != server.users.end(); it++)
	{
		if (it->nickname == nickname)
		{
			std::string result = ":";
			result += it->nickname + "!" + it->hostname + "@" + it->servername;
			return result;
		}
	}
	return std::string("");
}

void        IrcAPI::cmd_nick(Server& server, Client& client, const t_command& command)
{
    if (command.params.size() == 0)
		throw IrcException(ERR_NONICKNAMEGIVEN);
	if (client.is_registered && nick_in_use(server, command.params[0]))
		throw IrcException(ERR_NICKNAMEINUSE);
	if (!client.is_registered && nick_in_use(server, command.params[0]))
		throw IrcException(ERR_NICKCOLLISION);
	client.name = command.params[0]; // length of name should be 9 symbols
}