/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:23:18 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/19 06:12:06 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void    IrcAPI::cmd_oper(Server& server, Client& client, const t_command& command)
{
	if (client.status == SERVER)
		return;
    if (command.amount_of_params < 2)
	{
		sendReply(server, ERR_NEEDMOREPARAMS, "OPER :Not enough parameters", client);
		return ;
	}
    if (command.params[1] != server.password)
    {
		sendReply(server, ERR_PASSWDMISMATCH, ":Password incorrect", client);
        return ;
    }
    for (size_t i = 0; i < server.users.size(); i++)
    {
        if (server.users[i].nickname == command.params[0])
        {
            server.users[i].ircOp = true;
			sendReply(server, RPL_YOUREOPER, ":You are now an IRC operator", client);
			std::string toPropagate = ":" + client.name + " MODE " + client.name + " +o";
			server.propagate(toPropagate, client.name);
			break;
		}
	}
}