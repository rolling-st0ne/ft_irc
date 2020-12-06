/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 05:35:28 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/06 01:18:31 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

Channel*	IrcAPI::channel_by_name(Server& server, const std::string& name)
{
	for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
	{
		if (it->name == name)
			return (&*it);
	}
	return NULL;
}

void        IrcAPI::cmd_join(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 1)
	{
		sendReply(ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters", client);
		return ;
	}
	std::vector<std::string> channels = strsplit(command.params[0], ',');
	for (size_t i = 0; i < channels.size(); i++)
	{
		Channel* channel_ptr = channel_by_name(server, channels[i]);
		if (!channel_ptr)
			server.channels.push_back(Channel(channels[i], client.name));
		else
		{
			std::string message = user_by_nick(server, client.name) + " " + "JOIN " + channels[i];
			for (size_t i = 0; i < channel_ptr->members.size(); i++)
			{
				sendToUser(server, channel_ptr->members[i], message);
			}
			channel_ptr->addUser(client.name);
		}
		channel_ptr = channel_by_name(server, channels[i]);
		client.response += user_by_nick(server, client.name) + " " + "JOIN " + channels[i] + "\r\n";
		if (channel_ptr->topic == "")
			sendReply(RPL_NOTOPIC, channels[i] + " :No topic is set", client);
		else
			sendReply(RPL_TOPIC, channels[i] + " :" + channel_ptr->topic, client);
		std::string member_list = "";
		for (size_t i = 0; i < channel_ptr->members.size(); i++)
			member_list += channel_ptr->members[i] + " ";
		sendReply(RPL_NAMREPLY, " = " + channels[i] + " :" + member_list, client);
		sendReply(RPL_ENDOFNAMES, channels[i] + " :End of NAMES list", client);
	}
}