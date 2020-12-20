/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 06:34:10 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/20 10:20:16 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_topic(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 1)
	{
		sendReply(server, ERR_NEEDMOREPARAMS, "TOPIC :Not enough parameters", client);
		return ;
	}
	std::string channel = command.params[0];
	std::string topic;
	if (command.amount_of_params == 2)
		topic = command.params[1];
	else
		topic = "___show topic___";
	if (client.status == SERVER)
	{
		Channel* channel_ptr = channel_by_name(server, channel);
		if (!channel_ptr)
			return;
		channel_ptr->topic = topic;
		std::string notification = user_by_nick(server, command.prefix.substr(1)) + " TOPIC " + channel + " " + topic;
		for (size_t i = 0; i < channel_ptr->members.size(); i++)
			sendToUser(server, channel_ptr->members[i], notification);
		std::string toPropagate = command.prefix + " TOPIC " + channel + " " + topic;
		server.propagate(toPropagate, client.name);
		return;
	}
	for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
	{
		if (compareLower(it->name, channel))
		{
			if (!it->isUser(client.name))
			{
				sendReply(server, ERR_NOTONCHANNEL, channel + " :You're not on that channel", client);
				break;
			}
			if (topic == "___show topic___")
			{
				if (it->topic == "")
					sendReply(server, RPL_NOTOPIC, channel + " :No topic is set", client);
				else
					sendReply(server, RPL_TOPIC, channel + " " + it->topic, client);
				break;
			}
			if (!it->isOperator(client.name))
			{
				sendReply(server, ERR_CHANOPRIVSNEEDED, it->name + " :You're not channel operator", client);
				return;
			}
			it->topic = topic;
			std::string message = user_by_nick(server, client.name) + " TOPIC " + channel + " " + topic;
			for (size_t i = 0; i < it->members.size(); i++)
			{
				sendToUser(server, it->members[i], message);
			}

			std::string toPropagate = ":" + client.name + " TOPIC " + channel + " " + topic;
			server.propagate(toPropagate, client.name);
			break;
		}
	}	
}