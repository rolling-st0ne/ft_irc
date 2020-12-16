/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   njoin.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 11:59:32 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/16 09:05:45 by gwynton          ###   ########.fr       */
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
	std::vector<std::string> members = strsplit(command.params[1], ',');
	Channel* channel_ptr = channel_by_name(server, channel);
	if (!channel_ptr)
	{
		//server.channels.push_back(Channel(channel,))
	}
	std::string toPropagate = ":" + client.name + " NJOIN " + command.params[0] + ' ' + command.params[1];
	server.propagate(toPropagate, client.name);
}