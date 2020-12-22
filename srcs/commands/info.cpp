/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:51:31 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/22 11:26:57 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_info_end(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 2)
		return ;
	std::string user = command.params[0];
	std::string info = command.params[1];
	std::string message = ":" + server.name + " ";
	message += RPL_ENDOFINFO;
	message += " " + user + " " + info;
	if (sendToUser(server, user, message))
		return ;
	std::string toPropagate = message;
	server.propagate(toPropagate, client.name);
}

void        IrcAPI::cmd_info_response(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 2)
		return ;
	std::string user = command.params[0];
	std::string info = command.params[1];
	std::string message = ":" + server.name + " ";
	message += RPL_INFO;
	message += " " + user + " " + info;
	if (sendToUser(server, user, message))
		return ;
	std::string toPropagate = message;
	server.propagate(toPropagate, client.name);
}

void        IrcAPI::cmd_info(Server& server, Client& client, const t_command& command)
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
			std::string info_end = ":End of INFO list";
			sendReply(server, RPL_ENDOFINFO, info_end, client);
			return ;
		}
		std::string toPropagate = ":" + client.name + " INFO " + target;
		server.propagate(toPropagate, client.name);
	}
}
