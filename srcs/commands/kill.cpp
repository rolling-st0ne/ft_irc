/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 14:42:23 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/18 16:38:07 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void    IrcAPI::cmd_kill(Server& server, Client& client, const t_command& command)
{
    if (command.amount_of_params < 2)
	{
		sendReply(server, ERR_NEEDMOREPARAMS, "KILL :Not enough parameters", client);
		return ;
	}
    std::string target = command.params[0];
    std::string comment = command.params[1];
    bool target_found = false;
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
        sendReply(server, ERR_NOSUCHNICK, target + " :No such nick/channel", client);
        return ;
    }
    std::string killer = client.status == SERVER ? command.prefix.substr(1) : client.name;
    for (std::vector<Client>::iterator it = server.clients.begin(); it != server.clients.end(); it++)
    {
        if (it->name == target)
        {
            t_command quit_command;
            quit_command.prefix = "";
            quit_command.amount_of_params = 1;
            quit_command.command = "QUIT";
            quit_command.params.push_back(":Killed by " + killer);
            cmd_quit(server, *it, quit_command);
            return ;
        }
    }
    //std::cerr << "Delegating kill\n";
    std::string toPropagate = ":" + killer + " KILL " + target + " " + comment;
    server.propagate(toPropagate, client.name);
}