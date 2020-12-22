/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squit.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 07:27:31 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/22 23:32:29 by gwynton          ###   ########.fr       */
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
}
