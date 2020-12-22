/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:51:31 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/22 17:49:11 by gwynton          ###   ########.fr       */
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
			std::string info1 = ":This is " + target + " version 1.42";
			sendReply(server, RPL_INFO, info1, client);
			std::string info2 = ":Server started " + server.getStartTime();
			sendReply(server, RPL_INFO, info2, client);
			std::string info_end = ":End of INFO list";
			sendReply(server, RPL_ENDOFINFO, info_end, client);
			return ;
		}
		std::string toPropagate = ":" + client.name + " INFO " + target;
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
			client.response += RPL_INFO;
			client.response += " " + user;
			client.response += " :This is " + target + " version 1.42";
			client.response += "\r\n";
			client.response += ":" + server.name + " ";
			client.response += RPL_INFO;
			client.response += " " + user;
			client.response += " :Server started " + server.getStartTime();
			client.response += "\r\n";
			client.response += ":" + server.name + " ";
			client.response += RPL_ENDOFINFO;
			client.response += " " + user;
			client.response += " :End of INFO list";
			client.response += "\r\n";
			return;
		}
		std::string toPropagate = command.prefix + " TIME " + target;
		server.propagate(toPropagate, client.name);
	}
}
