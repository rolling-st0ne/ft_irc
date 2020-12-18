/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:42:43 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/18 09:30:59 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_mode(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 1)
	{
		sendReply(server, ERR_NEEDMOREPARAMS, "MODE :Not enough parameters", client);
		return;
	}
	if (client.status == SERVER)
	{
		if (command.amount_of_params < 3)
			return;
		std::string target = command.params[0];
		std::string modes = command.params[1];
		for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
		{
			if (it->name == target)
			{
				if (modes == "+o" || modes == "-o")
				{
					if (modes[0] == '+')
						it->addOperator(command.params[2]);
					else
						it->removeOperator(command.params[2]);
					for (size_t i = 0; i < it->members.size(); i++)
					{
						std::string message = ":" + server.name + " ";
						message += RPL_CHANNELMODEIS;
						message += " " + it->members[i] + " " + it->name + " " + modes + " " + command.params[2];
						sendToUser(server, it->members[i], message);
					}
				}
				break;
			}
		}
		std::string toPropagate = command.prefix + " MODE " + target + " " + modes + " " + command.params[2];
		server.propagate(toPropagate, client.name);
		return;
	}
	std::string target = command.params[0];
	std::string modes = command.amount_of_params < 2 ? "" : command.params[1];
	bool channel_found = false;
	for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
	{
		if (it->name == target)
		{
			channel_found = true;
			if (!it->isOperator(client.name))
			{
				sendReply(server, ERR_CHANOPRIVSNEEDED, it->name + " :You're not channel operator", client);
				return;
			}
			if (modes == "+o" || modes == "-o")
			{
				if (command.amount_of_params < 3)
				{
					sendReply(server, ERR_NEEDMOREPARAMS, "MODE :Not enough parameters", client);
					return;
				}
				if (!it->isUser(command.params[2]))
				{
					sendReply(server, ERR_USERNOTINCHANNEL, command.params[2] + " " + it->name + " :They aren't on that channel", client);
					return;
				}
				if (modes[0] == '+')
					it->addOperator(command.params[2]);
				else
					it->removeOperator(command.params[2]);
				for (size_t i = 0; i < it->members.size(); i++)
				{
					std::string message = ":" + server.name + " ";
					message += RPL_CHANNELMODEIS;
					message += " " + it->members[i] + " " + it->name + " " + modes + " " + command.params[2];
					sendToUser(server, it->members[i], message);
				}
				std::string toPropagate = ":" + client.name + " MODE " + target + " " + modes + " " + command.params[2];
				server.propagate(toPropagate, client.name);
				return ;
			}
		}
	}
}