/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:51:01 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/21 05:55:18 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_version(Server& server, Client& client, const t_command& command)
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
			std::string version_message = "1.42 " + server.name + " :December 2020";
			sendReply(server, RPL_VERSION, version_message, client);
			return ;
		}
		std::string toPropagate = ":" + client.name + " VERSION " + target;
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
			client.response += RPL_VERSION;
			client.response += " " + user + " ";
			client.response += "1.42 " + server.name + " :December 2020";
			client.response += "\r\n";
			return;
		}
		std::string toPropagate = command.prefix + " VERSION " + target;
		server.propagate(toPropagate, client.name);
	}
}
