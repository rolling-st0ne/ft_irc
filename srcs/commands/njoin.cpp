/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   njoin.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 11:59:32 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/17 06:30:25 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_njoin(Server& server, Client& client, const t_command& command)
{
	if (client.status == USER)
		return ;
	if (command.amount_of_params < 2)
	{
		sendReply(server, ERR_NEEDMOREPARAMS, "NJOIN :Not enough parameters", client);
		return ;
	}
	std::string channel = command.params[0];
	std::string inhabitants = command.params[1];
	if (inhabitants[0] == ':')
		inhabitants = inhabitants.substr(1);
	std::vector<std::string> members = strsplit(inhabitants, ',');
	Channel* channel_ptr = channel_by_name(server, channel);
	if (!channel_ptr)
	{
		server.channels.push_back(Channel(channel));
		channel_ptr = channel_by_name(server, channel);
		for (size_t i = 0; i < members.size(); i++)
		{
			if (members[i][0] == '@')
			{
				channel_ptr->addUser(members[i].substr(1));
				channel_ptr->addOperator(members[i].substr(1));
			}
			else
				channel_ptr->addUser(members[i]);
		}
	}
	else
	{
		for (size_t i = 0; i < members.size(); i++)
		{
			std::string newname = members[i];
			if (newname[0] == '@')
			{
				newname = newname.substr(1);
				channel_ptr->addOperator(newname);
			}
			channel_ptr->addUser(newname);
			std::string message = ":" + newname + " JOIN " + channel;
			for (size_t i = 0; i < channel_ptr->members.size(); i++)
			{
				sendToUser(server, channel_ptr->members[i], message);
			}
		}
	}
	std::string toPropagate = ":" + client.name + " NJOIN " + command.params[0] + ' ' + command.params[1];
	server.propagate(toPropagate, client.name);
}