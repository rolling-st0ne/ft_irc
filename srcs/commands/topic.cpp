/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 06:34:10 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/12 06:08:20 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_topic(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 1)
	{
		sendReply(ERR_NEEDMOREPARAMS, "TOPIC :Not enough parameters", client);
		return ;
	}
	std::string channel = command.params[0];
	std::string topic;
	if (command.amount_of_params == 2)
		topic = command.params[1];
	else
		topic = "___show topic___";
	for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
	{
		if (it->name == channel)
		{
			if (!it->isUser(client.name))
			{
				sendReply(ERR_NOTONCHANNEL, channel + " :You're not on that channel", client);
				break;
			}
			if (topic == "___show topic___")
			{
				if (it->topic == "")
					sendReply(RPL_NOTOPIC, channel + " :No topic is set", client);
				else
					sendReply(RPL_TOPIC, channel + " :" + it->topic, client);
				break;
			}
			if (!it->isOperator(client.name))
			{
				sendReply(ERR_CHANOPRIVSNEEDED, it->name + " :You're not channel operator", client);
				return;
			}
			it->topic = topic;
			std::string message = user_by_nick(server, client.name) + " " + "TOPIC " + channel + " " + topic;
			for (size_t i = 0; i < it->members.size(); i++)
			{
				sendToUser(server, it->members[i], message);
			}
			break;
		}
	}	
}