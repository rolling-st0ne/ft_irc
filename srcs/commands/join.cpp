/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 05:35:28 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/03 07:33:06 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_join(Server& server, Client& client, const t_command& command)
{
	std::vector<std::string> channels = strsplit(command.params[0], ',');
	for (size_t i = 0; i < channels.size(); i++)
	{
		bool found = false;
		for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
		{
			if (it->name == channels[i])
			{
				if (it->addUser(client.name))
					client.response += "Welcome to " + it->name + "!\r\n";
				found = true;
				break;
			}
		}
		if (!found)
			server.channels.push_back(Channel(channels[i], client.name));
	}

	// client.buffer.response += "JOIN " + command.params[0] + " " + client.name + "\r\n";
	// client.buffer.response += RPL_NOTOPIC;
	// client.buffer.response += " " + command.params[0] + " :No topic is set\r\n";
	// client.buffer.response += RPL_NAMREPLY;
	// client.buffer.response += " =" + command.params[0] + " @" + client.name + "\r\n";
	// client.buffer.response += RPL_ENDOFNAMES;
	// client.buffer.response += "\r\n";
}