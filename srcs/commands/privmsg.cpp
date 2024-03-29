/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 05:37:24 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/23 12:59:45 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

bool		IrcAPI::sendToUser(Server& server, std::string& target, std::string message)
{
	std::vector<Client>::iterator ite = server.clients.end();
	for (std::vector<Client>::iterator it = server.clients.begin(); it != ite; it++)
	{
		if (it->name == target)
		{
			it->response += message;
			it->response += "\r\n";
			return true;
		}
	}
	return false;
}

void        IrcAPI::cmd_privmsg(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 1)
	{
		sendReply(server, ERR_NORECIPIENT, ":No recipient given (PRIVMSG)", client);
		return ;
	}
	if (command.amount_of_params < 2)
	{
		sendReply(server, ERR_NOTEXTTOSEND, ":No text to send", client);
		return ;
	}
	std::vector<std::string> targets = strsplit(command.params[0], ',');
	for (size_t i = 0; i < targets.size(); i++)
	{
		bool found = false;
		std::string prefix;
		std::string toPropagate;
		std::string source;
		if (client.status == USER)
		{
			prefix = user_by_nick(server, client.name);
			toPropagate = ":" + client.name;
			source = client.name;
		}
		else
		{
			prefix = command.prefix;
			toPropagate = prefix;
			source = command.prefix.substr(1);
		}
		std::string message = " PRIVMSG " + targets[i] + " " + command.params[1];
		for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
		{
			bool sent_to_channel = false;
			if (compareLower(it->name, targets[i]))
			{
				std::vector<std::string>::iterator ite = it->members.end();
				for (std::vector<std::string>::iterator iter = it->members.begin(); iter != ite; iter++)
				{
					if (*iter != source && !sendToUser(server, *iter, prefix + message))
					{
						if (!sent_to_channel)
						{
							message = " PRIVMSG " + targets[i] + " " + command.params[1];
							server.propagate(toPropagate + message, client.name);
							sent_to_channel = true;
						}
					}
				}
				found = true;
				break;
			}
		}
		if (!found && !sendToUser(server, targets[i], prefix + message))
			server.propagate(toPropagate + message, client.name);
	}
}