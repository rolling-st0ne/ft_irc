/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 08:14:22 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/18 05:17:53 by gwynton          ###   ########.fr       */
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
	if (client.status == SERVER)
	{
		std::string user = command.prefix.substr(1);
		std::string message = command.amount_of_params == 2 ? command.params[1] : ":Leaving";
		std::string channel = command.params[0];
		//std::cerr << user << " has left " + channel << std::endl;
		Channel* channel_ptr = channel_by_name(server, channel);
		if (!channel_ptr)
			return;
		std::string notification = user_by_nick(server, user) + " PART " + channel + " " + message;
		for (size_t i = 0; i < channel_ptr->members.size(); i++)
			sendToUser(server, channel_ptr->members[i], notification);
		channel_ptr->removeUser(user);
		if (channel_ptr->members.size() == 0)
		{
			for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
			{
				if (it->name == channel)
				{
					server.channels.erase(it);
					break;
				}
			}
		}
		std::string toPropagate = command.prefix + " PART " + channel + " " + message;
		server.propagate(toPropagate, client.name);
		return ;
	}
	std::string leave_message;
	if (command.amount_of_params == 2)
		leave_message = command.params[1];
	else
		leave_message = client.name;
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
				std::string message = user_by_nick(server, client.name) + " PART " + channels[i] + " " + leave_message;
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
		std::string toPropagate = ":" + client.name + " PART " + channels[i] + " " + leave_message;
		server.propagate(toPropagate, client.name);
	}
}