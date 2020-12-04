/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 06:34:10 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/04 06:46:13 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_topic(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 1)
		return;
	std::string channel = command.params[0];
	std::string topic;
	if (command.amount_of_params == 2)
		topic = command.params[1];
	else
		topic = "";
	for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
	{
		if (it->name == channel)
		{
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