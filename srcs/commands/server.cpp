/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:07:05 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/13 06:48:33 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_server(Server& server, Client& client, const t_command& command)
{
	if (client.status)
		sendReply(ERR_ALREADYREGISTRED, ":Unauthorized command (already registered)", client);
	else if (client.password != server.password)
		sendReply(ERR_PASSWDMISMATCH, ":Password incorrect", client);
	else if (command.amount_of_params < 3)
		sendReply(ERR_NEEDMOREPARAMS, "SERVER :Not enough parameters", client);
	else
	{
		unsigned int hopcount = atoi(command.params[1].c_str());
		server.addHost(Host(command.params[0], hopcount, 0, command.params[2]));
		// add to connected servers if hopcount == 1
		client.status = SERVER;
		client.name = command.params[0];
	#ifdef DEBUG_MODE
		std::cerr << "Server " << client.name << " has been registered\n";
	#endif
	}
}