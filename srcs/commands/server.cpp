/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:07:05 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/16 08:27:42 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void				IrcAPI::throwServers(Server& server, Client& client, const t_command& command)
{
	std::string		message;
	for (std::vector<Host>::iterator it = server.hosts.begin(); it != server.hosts.end(); it++)
	{
		if (it->servername != server.name && it->servername != client.name)
		{
			message = ":" + server.name + " SERVER " + it->servername + ' ' + toString(it->hopcount) + ' ' + it->info + "\r\n";
			send(client.sock.socket_fd, message.c_str(), message.size(), 0);
		}
	}
	(void)command;
}

void				IrcAPI::throwUsers(Server& server, Client& client, const t_command& command)
{
	std::string		message;
	for (std::vector<User>::const_iterator it = server.users.begin(); it != server.users.end(); it++)
	{
		message.clear();
		message = ":" + server.name;
		message += " NICK " + it->nickname + ' ' + toString(it->hopcount) + ' ' + it->username +
				  ' ' + it->hostname + ' ' + '0' + ' ' + '+' + ' ' + it->realname;
		message += "\r\n";
		send(client.sock.socket_fd, message.c_str(), message.size(), 0);
	}
	(void)command;
}

void				IrcAPI::throwChannels(Server& server, Client& client, const t_command& command)
{
	std::string		message;

	for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
	{
		message.clear();
		message = ":" + server.name + " NJOIN " + it->name + ' ';
		for (std::vector<std::string>::iterator it1 = it->members.begin(); it1 != it->members.end(); it1++)
		{
			if (it->isOperator(*it1))
				message += '@';
			message += *it1 + ',';
		}
		message = message.substr(0, message.size() - 1);
		message += "\r\n";
		send(client.sock.socket_fd, message.c_str(), message.size(), 0);
	}
	(void)command;
}

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
			message = ":" + server.name + buildMessage(to_broadcast);
			sendToUser(server, *it, message);
		}
	}
}

void				IrcAPI::dataExchange(Server& server, Client& client, const t_command& command)
{
	throwServers(server, client, command);
	throwUsers(server, client, command);
	throwChannels(server,client, command);
}

void				IrcAPI::introduceHostToNet(Server& server, Client& client, const t_command& command)
{
	unsigned int hopcount = atoi(command.params[1].c_str());
	server.addHost(Host(command.params[0], hopcount, command.params[2]));
	client.name = command.params[0];
	server.connected_servers.push_back(client.name);

	std::string	reply;
	if (client.status != WAITING_FOR_CONNECTION)
	{
		reply = "PASS " + server.password + " 0210 IRC|\r\n";
		reply += "SERVER " + server.name + " 1 info\r\n";
		send(client.sock.socket_fd, reply.c_str(), reply.size(), 0);
	}
	client.status = SERVER;
	broadcastMessage(server, client, command);
	dataExchange(server, client, command);
}

void				IrcAPI::addHostToList(Server &server, Client& client, const t_command& command)
{
	unsigned int hopcount = atoi(command.params[1].c_str());
	server.addHost(Host(command.params[0], hopcount, command.params[2]));
	broadcastMessage(server, client, command);
//	if (hopcount == 1)
//		server.connected_servers.push_back(client.name);
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
		if (client.status == CLIENT || client.status == WAITING_FOR_CONNECTION) // add !is_registered
			introduceHostToNet(server, client, command);
		else if (client.status == SERVER)
			addHostToList(server, client, command);
	#ifdef DEBUG_MODE
		std::cerr << "Server " << command.params[0] << " has been registered\n";
	#endif
	}
}