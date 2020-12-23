/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squit.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 07:27:31 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/23 06:57:51 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_squit(Server& server, Client& client, const t_command& command)
{
	if (client.status == USER)
    {
        bool isOperator = false;
        for (size_t i = 0; i < server.users.size(); i++)
        {
            if (server.users[i].nickname == client.name && server.users[i].ircOp)
            {
                isOperator = true;
                break;
            }
        }
        if (!isOperator)
        {
            sendReply(server, ERR_NOPRIVILEGES, ":Permission Denied- You're not an IRC operator", client);
            return ;
        }
    }
    if (command.amount_of_params < 2)
	{
		sendReply(server, ERR_NEEDMOREPARAMS, "SQUIT :Not enough parameters", client);
		return ;
	}
    std::string target = command.params[0];
    std::string comment = command.params[1];
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
	std::string killer = client.status == SERVER ? command.prefix.substr(1) : client.name;
	if (server.name == target)
	{
		//std::cerr << "Cutting off " + target + " (" + comment + ")\n";
		for (std::vector<Client>::iterator it = server.clients.begin(); it != server.clients.end(); it++)
		{
			for (size_t i = 0; i < server.users.size(); i++)
			{
				if (server.users[i].nickname == it->name)
				{
					std::string quit_message = ":" + it->name + " QUIT :Server gone";
					server.propagate(quit_message, server.name);
					break;
				}
			}
		}
		server.forcedQuit = true;
		return;
	}
	std::string toPropagate = ":" + killer + " SQUIT " + target + " " + comment;
	server.propagate(toPropagate, client.name);
}
