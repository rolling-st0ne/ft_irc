/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 08:42:49 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/23 09:33:16 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_pong(Server& server, Client& client, const t_command& command)
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
    for (size_t i = 0; i < server.users.size(); i++)
    {
        if (server.users[i].nickname == target)
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
    if (server.name == target)
    {
        //std::cerr << "Received PONG from " + origin << std::endl;
        return;
    }
    for (size_t i = 0; i < server.clients.size(); i++)
    {
        if (server.clients[i].name == target)
        {
            server.clients[i].response += "PONG " + origin + "\r\n";
            return;
        }
    }
    std::string toPropagate = ":" + server.name + " PONG " + origin + " " + target;
    server.propagate(toPropagate, client.name);
}