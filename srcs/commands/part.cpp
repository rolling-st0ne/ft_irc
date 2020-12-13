/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 08:14:22 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/13 11:49:57 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_part(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 1)
	{
		sendReply(server, ERR_NEEDMOREPARAMS, "PART :Not enough parameters", client);
		return ;
	}

	std::string message;
	if (command.amount_of_params == 2)
		message = command.params[1];
	else
		message = client.name;
	std::vector<std::string> channels = strsplit(command.params[0], ',');
	for (size_t i = 0; i < channels.size(); i++)
	{
		bool channel_found = false;
		for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
		{
			if (it->name == channels[i])
			{
				channel_found = true;
				bool user_found = false;
				for (size_t i = 0; i < it->members.size(); i++)
				{
					if (it->members[i] == client.name)
					{
						user_found = true;
						break;
					}
				}
				if (!user_found)
				{
					sendReply(server, ERR_NOTONCHANNEL, channels[i] + " :You're not on that channel", client);
					break;
				}
				std::string message = user_by_nick(server, client.name) + " " + "PART " + channels[i];
				for (size_t i = 0; i < it->members.size(); i++)
					sendToUser(server, it->members[i], message);
				it->removeUser(client.name);
				if (it->members.size() == 0)
				{
					server.channels.erase(it);
				}
				break;
			}
		}
		if (!channel_found)
			sendReply(server, ERR_NOSUCHCHANNEL, channels[i] + " :No such channel", client);
	}
}