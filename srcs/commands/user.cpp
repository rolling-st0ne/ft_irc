/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:06:19 by casteria          #+#    #+#             */
/*   Updated: 2020/12/23 12:44:44 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_user(Server& server, Client& client, const t_command& command)
{
	if (client.status)
		sendReply(server, ERR_ALREADYREGISTRED, ":Unauthorized command (already registered)", client);
	else if (client.password != server.password)
		sendReply(server, ERR_PASSWDMISMATCH, ":Password incorrect", client);
	else if (command.amount_of_params != 4)
		sendReply(server, ERR_NEEDMOREPARAMS, "USER :Not enough parameters", client);
	else
	{
		server.users.push_back(User(client.name, command.params[0], command.params[1], command.params[2], command.params[3]));
		client.status = USER;
	#ifdef DEBUG_MODE
		std::cerr << "User " << client.name << " has been registered, real name: " << command.params[3] << std::endl;
	#endif
		std::string welcome_message = "Welcome to the Internet Relay Network " + user_by_nick(server, client.name).substr(1);
		sendReply(server, RPL_WELCOME, welcome_message, client);
		std::string your_host = "Your host is " + server.name + ", running version 1.42";
		sendReply(server, RPL_YOURHOST, your_host, client);
		std::string server_created = "This server was created in December 2020";
		sendReply(server, RPL_CREATED, server_created, client);
		std::string my_info = server.name + " 1.42 o";
		sendReply(server, RPL_MYINFO, my_info, client);
		std::string toPropagate = ":" + server.name + " NICK " + client.name + " 1 " + command.params[0];
		toPropagate += " " + command.params[1] + " 1 + " + command.params[3];
		server.propagate(toPropagate, "");
	}
}