/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:07:05 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/15 00:50:19 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

static void			incHopcount(t_command& command)
{
	std::stringstream	ss;
	ss << atoi(command.params[1].c_str()) + 1;
	command.params[1] = ss.str();
}

std::string			IrcAPI::buildMessage(const t_command& command)
{
	std::string		message = command.command + ' ';

	for (std::vector<std::string>::const_iterator it = command.params.begin(); it != command.params.end(); it++)
	{
		message += *it;
		if (it != command.params.end() - 1)
			message += ' ';
	}
#ifdef DEBUG_MODE
	std::cerr << "Builded message: " << message << std::endl;
#endif
	return (message);
}

void				IrcAPI::broadcastMessage(Server& server, Client& client, const t_command& command)
{
	t_command			to_broadcast = command;
	std::string			message;

	incHopcount(to_broadcast);
	for (std::vector<std::string>::iterator it = server.connected_servers.begin(); it != server.connected_servers.end(); it++)
	{
		if (*it != client.name)
		{
			message = buildMessage(to_broadcast);
			sendToUser(server, *it, message);
		}
	}
}

void				IrcAPI::dataExchange(Server& server, Client& client, const t_command& command)
{
	(void)server;
	(void)client;
	(void)command;
}

void				IrcAPI::introduceHostToNet(Server& server, Client& client, const t_command& command)
{
	unsigned int hopcount = atoi(command.params[1].c_str());
	client.status = SERVER;
	server.addHost(Host(command.params[0], hopcount, command.params[2]));
	client.name = command.params[0];
	server.connected_servers.push_back(client.name);
	dataExchange(server, client, command);
	broadcastMessage(server, client, command);
	server.connected_servers.push_back(client.name);
	(void)command;
	
}
void				IrcAPI::addHostToList(Server &server, Client& client, const t_command& command)
{
	unsigned int hopcount = atoi(command.params[1].c_str());
	server.addHost(Host(command.params[0], hopcount, command.params[2]));
	hopcount++;
	broadcastMessage(server, client, command);
	(void)client;
	(void)command;
}

void            IrcAPI::cmd_server(Server& server, Client& client, const t_command& command)
{
//	if (client.status)
//		sendReply(server, ERR_ALREADYREGISTRED, ":Unauthorized command (already registered)", client);
	if (client.password != server.password)
		sendReply(server, ERR_PASSWDMISMATCH, ":Password incorrect", client);
	else if (command.amount_of_params < 3)
		sendReply(server, ERR_NEEDMOREPARAMS, "SERVER :Not enough parameters", client);
	else
	{
		if (client.status == CLIENT)
			introduceHostToNet(server, client, command);
		else
			addHostToList(server, client, command);
	#ifdef DEBUG_MODE
		std::cerr << "Server " << client.name << " has been registered\n";
	#endif
	}
}