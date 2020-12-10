/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:06:19 by casteria          #+#    #+#             */
/*   Updated: 2020/12/10 18:57:03 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_user(Server& server, Client& client, const t_command& command)
{
	if (client.status)
		sendReply(ERR_ALREADYREGISTRED, ":Unauthorized command (already registered)", client);
	else if (client.password != server.password)
		sendReply(ERR_PASSWDMISMATCH, ":Password incorrect", client);
	else if (command.amount_of_params != 4)
		sendReply(ERR_NEEDMOREPARAMS, "USER :Not enough parameters", client);
	else
	{
		server.users.push_back(User(client.name, command.params[1], command.params[2], command.params[3]));
		client.status = USER;
	#ifdef DEBUG_MODE
		std::cerr << "User " << client.name << " has been registered, real name: " << command.params[3] << std::endl;
	#endif
	}
}