/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 05:35:28 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/02 21:47:05 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_join(Server& server, Client& client, const t_command& command)
{
	for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
	{
		if (it->name == command.params[0])
		{
			if (it->addUser(client.name))
				client.response += "Welcome to " + it->name + "!\r\n";
			return ;
		}
	}
	server.channels.push_back(Channel(command.params[0], client.name));
	// client.buffer.response += "JOIN " + command.params[0] + " " + client.name + "\r\n";
	// client.buffer.response += RPL_NOTOPIC;
	// client.buffer.response += " " + command.params[0] + " :No topic is set\r\n";
	// client.buffer.response += RPL_NAMREPLY;
	// client.buffer.response += " =" + command.params[0] + " @" + client.name + "\r\n";
	// client.buffer.response += RPL_ENDOFNAMES;
	// client.buffer.response += "\r\n";
}