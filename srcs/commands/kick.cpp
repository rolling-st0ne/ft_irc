/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 11:58:29 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/18 09:03:49 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_kick(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 2)
	{
		sendReply(server, ERR_NEEDMOREPARAMS, "KICK :Not enough parameters", client);
		return;
	}
	std::string channel = command.params[0];
	std::string user = command.params[1];
	std::string kicker = client.status == SERVER ? command.prefix.substr(1) : client.name;
	std::string reason = command.amount_of_params == 3 ? command.params[2] : kicker;
	for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
	{
		if (it->name == channel)
		{
			if (!it->isOperator(kicker))
			{
				sendReply(server, ERR_CHANOPRIVSNEEDED, it->name + " :You're not channel operator", client);
				return;
			}
			if (!it->isUser(user))
			{
				sendReply(server, ERR_USERNOTINCHANNEL, user + " " + it->name + " :They aren't on that channel", client);
				return;
			}
			std::string message = user_by_nick(server, user) + " KICK " + channel + " " + user + " " + reason;
			for (size_t i = 0; i < it->members.size(); i++)
			{
				sendToUser(server, it->members[i], message);
			}
			it->removeUser(user);
			std::string toPropagate = ":" + kicker + " KICK " + channel + " " + user + " " + reason;
			server.propagate(toPropagate, client.name);
			break;
		}
	}
}