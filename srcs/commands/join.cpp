/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 05:35:28 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/04 02:53:15 by gwynton          ###   ########.fr       */
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
					;//client.response += "Welcome to " + it->name + "!\r\n";
				found = true;
				break;
			}
		}
		if (!found)
			server.channels.push_back(Channel(channels[i], client.name));
		std::string prefix = ":localhost ";
		
		std::string full_user = ":" + client.name + "!" + server.users[0].hostname + "@" + server.users[0].servername;
		client.response += full_user + " " + "JOIN " + channels[i] + "\r\n";
		client.response += prefix;
		client.response += RPL_NOTOPIC;
		client.response += " " + client.name + " " + channels[i] + " :No topic is set\r\n";
		client.response += prefix;
		client.response += RPL_NAMREPLY;
		client.response += " " + client.name + " = " + channels[i] + " :@" + client.name + " Shust\r\n";
		client.response += prefix;
		client.response += RPL_ENDOFNAMES;
		client.response += " " + client.name + " " + channels[i] + " :End of NAMES list\r\n";
	}
}