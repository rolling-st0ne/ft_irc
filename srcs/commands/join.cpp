/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 05:35:28 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/16 08:17:51 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

Channel*	IrcAPI::channel_by_name(Server& server, const std::string& name)
{
	for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
	{
		if (it->name == name)
		{
			return (&*it);
		}
	}
	return NULL;
}

void        IrcAPI::cmd_join(Server& server, Client& client, const t_command& command)
{
	if (client.status == SERVER)
	{
		bool new_operator = false;
		std::string target = command.params[0];
		if (command.params[0].size() > 1 && command.params[0][command.params[0].size() - 2] == '\7')
		{
			new_operator = true;
			target = target.substr(0, target.size() - 2);
		}
		std::string new_user = command.prefix.substr(1);
		Channel* channel_ptr = channel_by_name(server, target);
		if (!channel_ptr)
		{
			server.channels.push_back(Channel(target, new_user));
		}
		else
		{
			std::string message = command.prefix + " JOIN " + target;
			for (size_t i = 0; i < channel_ptr->members.size(); i++)
			{
				sendToUser(server, channel_ptr->members[i], message);
			}
			channel_ptr->addUser(new_user);
			if (new_operator)
				channel_ptr->addOperator(new_user);
		}
		std::string toPropagate = command.prefix + " JOIN " + target;
		if (new_operator)
			toPropagate += "\7o";
		server.propagate(toPropagate, client.name);
		return;
	}
	if (command.amount_of_params < 1)
	{
		sendReply(server, ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters", client);
		return ;
	}
	std::vector<std::string> channels = strsplit(command.params[0], ',');
	for (size_t i = 0; i < channels.size(); i++)
	{
		Channel* channel_ptr = channel_by_name(server, channels[i]);
		if (!channel_ptr)
		{
			server.channels.push_back(Channel(channels[i], client.name));
		}
		else
		{
			std::string message = user_by_nick(server, client.name) + " JOIN " + channels[i];
			for (size_t i = 0; i < channel_ptr->members.size(); i++)
			{
				sendToUser(server, channel_ptr->members[i], message);
			}
			channel_ptr->addUser(client.name);
		}
		channel_ptr = channel_by_name(server, channels[i]);
		client.response += user_by_nick(server, client.name) + " JOIN " + channels[i] + "\r\n";
		if (channel_ptr->topic == "")
			sendReply(server, RPL_NOTOPIC, channels[i] + " :No topic is set", client);
		else
			sendReply(server, RPL_TOPIC, channels[i] + " :" + channel_ptr->topic, client);
		std::string member_list = "";
		for (size_t i = 0; i < channel_ptr->members.size(); i++)
		{
			for (size_t j = 0; j < channel_ptr->operators.size(); j++)
			{
				if (channel_ptr->members[i] == channel_ptr->operators[j])
				{
					member_list += "@";
					break;
				}
			}
			member_list += channel_ptr->members[i] + " ";
		}
		sendReply(server, RPL_NAMREPLY, " = " + channels[i] + " :" + member_list, client);
		sendReply(server, RPL_ENDOFNAMES, channels[i] + " :End of NAMES list", client);
		std::string toPropagate = ":" + client.name + " JOIN " + channels[i];
		if (channel_ptr->isOperator(client.name))
			toPropagate += "\7o";
		server.propagate(toPropagate, "");
	}
}