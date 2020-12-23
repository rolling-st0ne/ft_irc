/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 10:43:11 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/23 11:15:38 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_invite(Server& server, Client& client, const t_command& command)
{
    if (command.amount_of_params < 2)
	{
		sendReply(server, ERR_NEEDMOREPARAMS, "KICK :Not enough parameters", client);
		return ;
	}
	std::string user = command.params[0];
	std::string channel = command.params[1];
    std::string inviter = client.status == SERVER ? command.prefix.substr(1) : client.name;
    bool user_found = false;
    for (size_t i = 0; i < server.users.size(); i++)
    {
        if (server.users[i].nickname == user)
        {
            user_found = true;
            break;
        }
    }
    if (!user_found)
    {
        sendReply(server, ERR_NOSUCHNICK, user + " :No such nick/channel", client);
        return ;
    }
    bool channel_found = false;
    for (size_t i = 0; i < server.channels.size(); i++)
    {
        if (compareLower(server.channels[i].name, channel))
        {
            channel_found = true;
            break;
        }
    }
    if (channel_found)
    {
        Channel* channel_ptr = channel_by_name(server, channel);
        if (!channel_ptr->isUser(inviter))
        {
            sendReply(server, ERR_NOTONCHANNEL, channel + " :You're not on that channel", client);
            return ;
        }
        if (channel_ptr->isUser(user))
        {
            sendReply(server, ERR_USERONCHANNEL, user + " " + channel + " :is already on channel", client);
            return ;
        }
    }
    if (client.status == USER)
        sendReply(server, RPL_INVITING, channel + " " + user, client);
    std::string invite_message = user_by_nick(server, inviter) + " INVITE " + user + " " + channel;
    if (sendToUser(server, user, invite_message))
        return ;
    std::string toPropagate = ":" + inviter + " INVITE " + user + " " + channel;
    server.propagate(toPropagate, client.name);
}
