/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 07:28:43 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/22 05:32:52 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_admin_response1(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 3)
		return;
	std::string user = command.params[0];
	std::string target = command.params[1];
	std::string info = command.params[2];
	std::string admin_message = ":" + server.name + " ";
	admin_message += RPL_ADMINME;
	admin_message += " " + user + " " + target + " " + info;
	if (sendToUser(server, user, admin_message))
		return;
	std::string toPropagate = admin_message;
	server.propagate(toPropagate, client.name);
}

void        IrcAPI::cmd_admin_response2(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 2)
		return;
	std::string user = command.params[0];
	std::string info = command.params[1];
	std::string admin_message = ":" + server.name + " ";
	admin_message += RPL_ADMINLOC1;
	admin_message += " " + user + " " + info;
	if (sendToUser(server, user, admin_message))
		return;
	std::string toPropagate = admin_message;
	server.propagate(toPropagate, client.name);
}

void        IrcAPI::cmd_admin_response3(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 2)
		return;
	std::string user = command.params[0];
	std::string info = command.params[1];
	std::string admin_message = ":" + server.name + " ";
	admin_message += RPL_ADMINLOC2;
	admin_message += " " + user + " " + info;
	if (sendToUser(server, user, admin_message))
		return;
	std::string toPropagate = admin_message;
	server.propagate(toPropagate, client.name);
}

void        IrcAPI::cmd_admin_response4(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 2)
		return;
	std::string user = command.params[0];
	std::string info = command.params[1];
	std::string admin_message = ":" + server.name + " ";
	admin_message += RPL_ADMINEMAIL;
	admin_message += " " + user + " " + info;
	if (sendToUser(server, user, admin_message))
		return;
	std::string toPropagate = admin_message;
	server.propagate(toPropagate, client.name);
}

void        IrcAPI::cmd_admin(Server& server, Client& client, const t_command& command)
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
			sendReply(server, RPL_ADMINME, server.name + " :Administrative info", client);
			sendReply(server, RPL_ADMINLOC1, ":Moscow", client);
			sendReply(server, RPL_ADMINLOC2, ":School 21", client);
			sendReply(server, RPL_ADMINEMAIL, ":gwynton@student.21-school.ru", client);
			return ;
		}
		std::string toPropagate = ":" + client.name + " ADMIN " + target;
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
			client.response += RPL_ADMINME;
			client.response += " " + user + " ";
			client.response += server.name + " :Administrative info";
			client.response += "\r\n";
			client.response += ":" + server.name + " ";
			client.response += RPL_ADMINLOC1;
			client.response += " " + user + " ";
			client.response += ":Moscow";
			client.response += "\r\n";
			client.response += ":" + server.name + " ";
			client.response += RPL_ADMINLOC2;
			client.response += " " + user + " ";
			client.response += ":School 21";
			client.response += "\r\n";
			client.response += ":" + server.name + " ";
			client.response += RPL_ADMINEMAIL;
			client.response += " " + user + " ";
			client.response += ":gwynton@student.21-school.ru";
			client.response += "\r\n";
			return ;
		}
		std::string toPropagate = command.prefix + " ADMIN " + target;
		server.propagate(toPropagate, client.name);
	}
}
