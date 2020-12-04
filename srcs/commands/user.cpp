/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:06:19 by casteria          #+#    #+#             */
/*   Updated: 2020/12/05 02:19:59 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_user(Server& server, Client& client, const t_command& command)
{
	if (client.is_registered)
	{
		client.response += ":localhost ";
		client.response += ERR_ALREADYREGISTRED;
		client.response += " " + client.name + " :Unauthorized command (already registered)\r\n";
	}
	else if (client.password != server.password)
	{
		client.response += ":localhost ";
		client.response += ERR_PASSWDMISMATCH;
		client.response += " " + client.name + " :Password incorrect\r\n";
	}
	else if (command.amount_of_params != 4)
	{
		client.response += ":localhost ";
		client.response += ERR_NEEDMOREPARAMS;
		client.response += " " + client.name + " USER :Not enough parameters\r\n";
	}
	else
	{
		server.users.push_back(User(client.name, command.params[1], command.params[2], command.params[3]));
		client.is_registered = true;
	#ifdef DEBUG_MODE
		std::cerr << "User " << client.name << " has been registered, real name: " << command.params[3] << std::endl;
	#endif
	}
}