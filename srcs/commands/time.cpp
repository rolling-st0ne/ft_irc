/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:51:17 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/22 08:00:20 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_time_response(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 3)
		return;
	std::string user = command.params[0];
	std::string target = command.params[1];
	std::string time = command.params[2];
	std::string time_message = ":" + server.name + " ";
	time_message += RPL_TIME;
	time_message += " " + user + " " + target + " " + time;
	if (sendToUser(server, user, time_message))
		return;
	std::string toPropagate = time_message;
	server.propagate(toPropagate, client.name);
}

void        IrcAPI::cmd_time(Server& server, Client& client, const t_command& command)
{
    if (client.status == USER)
	{
		std::string target = command.amount_of_params == 1 ? command.params[0] : server.name;
		bool serverFound = false;
		for (size_t i = 0; i < server.hosts.size(); i++)
		{
			if (server.hosts[i].servername == target)
			{
				serverFound = true;
				break;
			}
		}
		if (!serverFound)
		{
			sendReply(server, ERR_NOSUCHSERVER, target + " :No such server", client);
			return ;
		}
		if (server.name == target)
		{
			std::string time_message = server.name + " :" + server.getTimeString();
			sendReply(server, RPL_TIME, time_message, client);
			return ;
		}
		std::string toPropagate = ":" + client.name + " TIME " + target;
		server.propagate(toPropagate, client.name);
	}
	else if (client.status == SERVER)
	{
		if (command.amount_of_params < 1)
			return;
		std::string target = command.params[0];
		std::string user = command.prefix.substr(1);
		if (server.name == target)
		{
			client.response += ":" + server.name + " ";
			client.response += RPL_TIME;
			client.response += " " + user + " ";
			client.response += server.name + " :" + server.getTimeString();
			client.response += "\r\n";
			return;
		}
		std::string toPropagate = command.prefix + " TIME " + target;
		server.propagate(toPropagate, client.name);
	}
}
