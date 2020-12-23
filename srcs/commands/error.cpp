/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 10:15:06 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/23 10:27:14 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_error(Server& server, Client& client, const t_command& command)
{
    if (client.status == USER)
        return ;
    if (command.amount_of_params < 1)
        return ;
    std::string message = command.params[0];
    for (size_t i = 0; i < server.clients.size(); i++)
    {
        for (size_t j = 0; j < server.users.size(); j++)
        {
            if (server.clients[i].name == server.users[j].nickname && server.users[j].ircOp)
            {
                std::string error_message = ":" + server.name + " NOTICE " + server.clients[i].name + " " + message;
                sendToUser(server, server.clients[i].name, error_message);
                break;
            }
        }
    }
}