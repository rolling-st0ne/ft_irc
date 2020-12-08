/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 10:18:16 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/08 03:36:44 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void	IrcAPI::cmd_quit(Server& server, Client& client, const t_command& command)
{
	std::string away_message;
	if (command.amount_of_params > 0)
		away_message = command.params[0];
	else
		away_message = client.name;
	std::string message = user_by_nick(server, client.name) + " QUIT " + away_message;
	for (size_t i = 0; i < server.users.size(); i++)
	{
		if (server.users[i].nickname != client.name)
			sendToUser(server, server.users[i].nickname, message);
	}
	for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
	{
		for (size_t i = 0; i < it->members.size(); i++)
		{
			if (it->members[i] == client.name)
			{
				it->removeUser(client.name);
				break;
			}
		}
		if (it->members.size() == 0)
		{
			server.channels.erase(it);
			break;
		}
	}
	for (std::vector<User>::iterator it = server.users.begin(); it != server.users.end(); it++)
	{
		if (it->nickname == client.name)
		{
			server.users.erase(it);
			break;
		}
	}
	close(client.sock.socket_fd);
	client.sock.socket_fd = -1;
	client.response.clear();
}