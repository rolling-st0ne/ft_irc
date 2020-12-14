/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:07:05 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/14 04:42:57 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_server(Server& server, Client& client, const t_command& command)
{
	if (client.status)
		sendReply(server, ERR_ALREADYREGISTRED, ":Unauthorized command (already registered)", client);
	else if (client.password != server.password)
		sendReply(server, ERR_PASSWDMISMATCH, ":Password incorrect", client);
	else if (command.amount_of_params < 3)
		sendReply(server, ERR_NEEDMOREPARAMS, "SERVER :Not enough parameters", client);
	else
	{
		/*
		unsigned int hopcount = atoi(command.params[1].c_str());
		if (client.status == CLIENT)
			introduceHostToNet(client, command);
		else
			addHostToList(client, command);
		*/
		server.addHost(Host(command.params[0], hopcount, 0, command.params[2]));
		client.status = SERVER;
		client.name = command.params[0];
		if (hopcount == 1)
		{
			server.connected_servers.push_back(command.params[0]);
		}
	#ifdef DEBUG_MODE
		std::cerr << "Server " << client.name << " has been registered\n";
	#endif
	}
}