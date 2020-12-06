/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:10:11 by casteria          #+#    #+#             */
/*   Updated: 2020/12/06 01:30:59 by gwynton          ###   ########.fr       */
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
	{
		sendReply(ERR_NONICKNAMEGIVEN, ":No nickname given", client);
		return ;
	}
	if (nick_in_use(server, command.params[0]))
	{
		if (client.is_registered)
			sendReply(ERR_NICKNAMEINUSE, command.params[0] + " :Nickname is already in use", client);
		else
			sendReply(ERR_NICKCOLLISION, command.params[0] + " :Nickname collision", client); // TODO: add KILL
		return ;
	}
	std::string old_nick = client.name;
	client.name = command.params[0]; // length of name should be 9 symbols
	if (client.is_registered) // This gets reset somehow, I'll investigate
	{
		std::string message = user_by_nick(server, old_nick) + " NICK " + client.name;
		for (size_t i = 0; i < server.users.size(); i++)
		{
			//std::cerr << "Checking nick: " << server.users[i].nickname << std::endl;
			if (server.users[i].nickname == old_nick)
			{
				//std::cerr << "Changing " << old_nick << " to " << client.name << std::endl;
				server.users[i].nickname = client.name;
				break;
			}
		}
		for (size_t i = 0; i < server.users.size(); i++)
		{
			sendToUser(server, server.users[i].nickname, message);
		}
		for (size_t i = 0; i < server.channels.size(); i++)
		{
			for (size_t j = 0; j < server.channels[i].members.size(); j++)
			{
				if (server.channels[i].members[j] == old_nick)
					server.channels[i].members[j] = client.name;
			}
		}
	}
}