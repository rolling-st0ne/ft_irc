/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:10:11 by casteria          #+#    #+#             */
/*   Updated: 2020/12/16 04:03:52 by gwynton          ###   ########.fr       */
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
	if (client.status == SERVER)
	{
		if (command.amount_of_params == 1)
		{
			std::cerr << "Another server's user has changed their nick\n";
			std::string message = command.prefix + " NICK " + command.params[0];
			server.propagate(message, client.name);
			std::string old_nick = command.prefix.substr(1);
			std::string toUser = user_by_nick(server, old_nick) + " NICK " + command.params[0];
			for (size_t i = 0; i < server.users.size(); i++)
			{
				if (server.users[i].nickname == old_nick)
				{
					server.users[i].nickname = command.params[0];
					break;
				}
			}
			for (size_t i = 0; i < server.users.size(); i++)
			{
				sendToUser(server, server.users[i].nickname, toUser);
			}
			for (size_t i = 0; i < server.channels.size(); i++)
			{
				for (size_t j = 0; j < server.channels[i].members.size(); j++)
				{
					if (server.channels[i].members[j] == old_nick)
						server.channels[i].members[j] = command.params[0];
				}
				for (size_t j = 0; j < server.channels[i].operators.size(); j++)
				{
					if (server.channels[i].operators[j] == old_nick)
						server.channels[i].operators[j] = command.params[0];
				}
			}
		}
		else if (command.amount_of_params == 7)
		{
			server.users.push_back(User(command.params[0], command.params[2], command.params[3], "1", command.params[6]));
			std::string toPropagate = ":" + server.name + " NICK";
			for (int i = 0; i < 7; i++)
				toPropagate += " " + command.params[i];
			server.propagate(toPropagate, client.name);
		}
		return ;
	}
    if (command.params.size() == 0)
	{
		sendReply(server, ERR_NONICKNAMEGIVEN, ":No nickname given", client);
		return ;
	}
	if (nick_in_use(server, command.params[0]))
	{
		if (client.status)
			sendReply(server, ERR_NICKNAMEINUSE, command.params[0] + " :Nickname is already in use", client);
		else
			sendReply(server, ERR_NICKCOLLISION, command.params[0] + " :Nickname collision", client); // TODO: add KILL
		return ;
	}
	std::string old_nick = client.name;
	client.name = command.params[0]; // length of name should be 9 symbols
	if (client.status) // This gets reset somehow, I'll investigate
	{
		std::string message = user_by_nick(server, old_nick) + " NICK " + client.name;
		for (size_t i = 0; i < server.users.size(); i++)
		{
			if (server.users[i].nickname == old_nick)
			{
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
			for (size_t j = 0; j < server.channels[i].operators.size(); j++)
			{
				if (server.channels[i].operators[j] == old_nick)
					server.channels[i].operators[j] = client.name;
			}
		}
		std::string toPropagate = ":" + old_nick + " NICK " +command.params[0];
		server.propagate(toPropagate, client.name);
	}
}