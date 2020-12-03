/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 08:14:22 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/03 09:04:13 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_part(Server& server, Client& client, const t_command& command)
{
	std::string message;

	if (command.amount_of_params == 2)
		message = command.params[1];
	else
		message = client.name;
	std::vector<std::string> channels = strsplit(command.params[0], ',');
	for (size_t i = 0; i < channels.size(); i++)
	{
		for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
		{
			if (it->name == channels[i])
			{
				it->removeUser(client.name);
				if (it->members.size() == 0)
				{
					server.channels.erase(it);
				}
				break;
			}
		}
	}
}