/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 03:46:17 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/12 03:50:44 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_notice(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 1)
	{
		sendReply(ERR_NORECIPIENT, ":No recipient given (NOTICE)", client);
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
		std::string message = user_by_nick(server, client.name) + " NOTICE " + targets[i] + " " + command.params[1];
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
}