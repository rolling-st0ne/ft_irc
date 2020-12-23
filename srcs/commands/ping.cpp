/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 08:42:21 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/23 09:33:21 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_ping(Server& server, Client& client, const t_command& command)
{
    if (command.amount_of_params < 1)
    {
        sendReply(server, ERR_NOORIGIN, ":No origin specified", client);
        return;
    }
    std::string origin = command.params[0];
    std::string target = command.amount_of_params == 2 ? command.params[1] : server.name;
    bool target_found = false;
	for (size_t i = 0; i < server.hosts.size(); i++)
	{
		if (server.hosts[i].servername == target)
		{
			target_found = true;
			break;
		}
	}
	if (!target_found)
	{
		sendReply(server, ERR_NOSUCHSERVER, target + " :No such server", client);
		return;
	}
    if (target == server.name)
    {
        //std::cerr << "Received PING from " + origin << std::endl;
        for (size_t i = 0; i < server.clients.size(); i++)
        {
            if (server.clients[i].name == origin)
            {
                server.clients[i].response += "PONG " + server.name + "\r\n";
                return;
            }
        }
        std::string toPropagate = ":" + server.name + " PONG " + server.name + " " + origin;
        server.propagate(toPropagate, server.name);
        return;
    }
    std::string toPropagate = ":" + server.name + " PING " + origin + " " + target;
    server.propagate(toPropagate, client.name);
}