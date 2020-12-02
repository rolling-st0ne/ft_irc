/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 05:37:24 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/02 22:00:29 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void		IrcAPI::sendToUser(Server& server, std::string& target, std::string& message)
{
	std::vector<Client>::iterator ite = server.clients.end();
	for (std::vector<Client>::iterator it = server.clients.begin(); it != ite; it++)
	{
		//std::cerr << "Checking name: " << it->name << std::endl;
		if (it->name == target)
		{
			//std::cerr << "Sending " + message + " to " + target << std::endl;
			it->response += message + "\r\n";
		}
	}
}

void        IrcAPI::cmd_privmsg(Server& server, Client& client, const t_command& command)
{
	if (command.amount_of_params != 2)
		return ;
	std::string target = command.params[0];
	std::string message = command.params[1];
	for (std::vector<Channel>::iterator it = server.channels.begin(); it != server.channels.end(); it++)
	{
		if (it->name == target)
		{
			std::vector<std::string>::iterator ite = it->members.end();
			for (std::vector<std::string>::iterator iter = it->members.begin(); iter != ite; iter++)
			{
				sendToUser(server, *iter, message);
			}
			return ;
		}
	}
	sendToUser(server, target, message);
	(void)client;
}