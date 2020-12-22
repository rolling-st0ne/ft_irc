/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 07:28:25 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/22 11:01:49 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_stats_end(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 3)
		return ;
	std::string user = command.params[0];
	std::string letter = command.params[1];
	std::string info = command.params[2];
	std::string message = ":" + server.name + " ";
	message += RPL_ENDOFSTATS;
	message += " " + user + " " + letter + " " + info;
	if (sendToUser(server, user, message))
		return ;
	std::string toPropagate = message;
	server.propagate(toPropagate, client.name);
}

void        IrcAPI::cmd_stats_uptime(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params < 2)
		return ;
	std::string user = command.params[0];
	std::string info = command.params[1];
	std::string message = ":" + server.name + " ";
	message += RPL_STATSUPTIME;
	message += " " + user + " " + info;
	if (sendToUser(server, user, message))
		return ;
	std::string toPropagate = message;
	server.propagate(toPropagate, client.name);
}

void        IrcAPI::cmd_stats(Server& server, Client& client, const t_command& command)
{
	if (client.status == USER)
	{
		std::string target;
		char	letter;
		if (command.amount_of_params == 0)
		{
			letter = '*';
			target = server.name;
		}
		else if (command.amount_of_params == 1)
		{
			if (command.params[0].size() == 1)
			{
				letter = command.params[0][0];
				target = server.name;
			}
			else
			{
				letter = '*';
				target = command.params[0];
			}
		}
		else
		{
			letter = command.params[0][0];
			target = command.params[1];
		}
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
			//process
			if (letter == 'u')
			{
				std::string uptime = ":Server Up 0 days ";
				uptime += "get uptime";
				sendReply(server, RPL_STATSUPTIME, uptime, client);
			}
			std::string output = "  ";
			output[0] = letter;
			output += ":End of STATS report";
			sendReply(server, RPL_ENDOFSTATS, output, client);
			return ;
		}
		std::string toPropagate = ":" + client.name + " STATS " + letter + " " + target;
		server.propagate(toPropagate, client.name);
	}
	else if (client.status == SERVER)
	{
		std::string target;
		char letter;
		std::string user = command.prefix.substr(1);
		if (command.amount_of_params < 1)
			return;
		if (command.amount_of_params < 2)
		{
			letter = '*';
			target = command.params[0];
		}
		else
		{
			letter = command.params[0][0];
			target = command.params[1];
		}
		if (server.name == target)
		{
			//process
			client.response += ":" + server.name + " ";
			client.response += RPL_ENDOFSTATS;
			client.response += " " + user + " " + letter;
			client.response += " :End of STATS report";
			client.response += "\r\n";
			return ;
		}
		std::string toPropagate = command.prefix + " STATS " + letter + " " + target;
		server.propagate(toPropagate, client.name);
	}
}
