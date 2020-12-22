/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:49:54 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/22 21:13:32 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_motd_start(Server& server, Client& client, const t_command& command)
{
    if (command.amount_of_params < 2)
		return ;
	std::string user = command.params[0];
	std::string info = command.params[1];
	std::string message = ":" + server.name + " ";
	message += RPL_MOTDSTART;
	message += " " + user + " " + info;
	if (sendToUser(server, user, message))
		return ;
	std::string toPropagate = message;
	server.propagate(toPropagate, client.name);
}

void        IrcAPI::cmd_motd_response(Server& server, Client& client, const t_command& command)
{
    if (command.amount_of_params < 2)
		return ;
	std::string user = command.params[0];
	std::string info = command.params[1];
	std::string message = ":" + server.name + " ";
	message += RPL_MOTD;
	message += " " + user + " " + info;
	if (sendToUser(server, user, message))
		return ;
	std::string toPropagate = message;
	server.propagate(toPropagate, client.name);
}

void        IrcAPI::cmd_motd_end(Server& server, Client& client, const t_command& command)
{
    if (command.amount_of_params < 2)
		return ;
	std::string user = command.params[0];
	std::string info = command.params[1];
	std::string message = ":" + server.name + " ";
	message += RPL_ENDOFMOTD;
	message += " " + user + " " + info;
	if (sendToUser(server, user, message))
		return ;
	std::string toPropagate = message;
	server.propagate(toPropagate, client.name);
}

void        IrcAPI::cmd_motd(Server& server, Client& client, const t_command& command)
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
			std::string motd_start = ":- " + target + " Message of the day - ";
			sendReply(server, RPL_MOTDSTART, motd_start, client);
			std::string motd = ":- Happy new year!";
			sendReply(server, RPL_MOTD, motd, client);
			std::string motd_end = ":End of MOTD command";
			sendReply(server, RPL_ENDOFMOTD, motd_end, client);
			return ;
		}
		std::string toPropagate = ":" + client.name + " MOTD " + target;
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
			client.response += RPL_MOTDSTART;
			client.response += " " + user;
			client.response += " :- " + target + " Message of the day - ";
			client.response += "\r\n";
			client.response += ":" + server.name + " ";
			client.response += RPL_MOTD;
			client.response += " " + user;
			client.response += " :- Happy new year!";
			client.response += "\r\n";
			client.response += ":" + server.name + " ";
			client.response += RPL_ENDOFMOTD;
			client.response += " " + user;
			client.response += " :End of MOTD command";
			client.response += "\r\n";
			return;
		}
		std::string toPropagate = command.prefix + " MOTD " + target;
		server.propagate(toPropagate, client.name);
	}
}
