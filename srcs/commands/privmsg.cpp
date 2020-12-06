/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 05:37:24 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/06 03:12:06 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void		IrcAPI::sendToUser(Server& server, std::string& target, std::string& message)
{
	std::vector<Client>::iterator ite = server.clients.end();
	for (std::vector<Client>::iterator it = server.clients.begin(); it != ite; it++)
	{
		if (it->name == target)
		{
			it->response += message + "\r\n";
		}
	}
}

void        IrcAPI::cmd_privmsg(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 1)
	{
		sendReply(ERR_NORECIPIENT, ":No recipient given (PRIVMSG)", client);
		return ;
	}
	if (command.amount_of_params < 2)
	{
		sendReply(ERR_NOTEXTTOSEND, ":No text to send", client);
		return ;
	}
	std::vector<std::string> targets = strsplit(command.params[0], ',');
	for (size_t i = 0; i < targets.size(); i++)
	{
		bool found = false;
		std::string message = user_by_nick(server, client.name) + " PRIVMSG " + targets[i] + " " + command.params[1];
		for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
		{
			if (it->name == targets[i])
			{
				std::vector<std::string>::iterator ite = it->members.end();
				for (std::vector<std::string>::iterator iter = it->members.begin(); iter != ite; iter++)
				{
					if (*iter != client.name)
						sendToUser(server, *iter, message);
				}
				found = true;
				break;
			}
		}
		if (!found)
			sendToUser(server, targets[i], message);
	}
	(void)client;
}