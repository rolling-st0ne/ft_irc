/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:06:19 by casteria          #+#    #+#             */
/*   Updated: 2020/12/02 05:50:43 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_user(Server& server, Client& client, const t_command& command)
{
	if (client.is_registered)
		throw IrcException(ERR_ALREADYREGISTRED);
	if (client.password != server.password)
		throw IrcException(ERR_PASSWDMISMATCH);
	if (command.amount_of_params != 4)
		throw IrcException(ERR_NEEDMOREPARAMS);
	server.users.push_back(User(client.name, command.params[1], command.params[2], command.params[3]));
	client.is_registered = true;
#ifdef DEBUG_MODE
	std::cerr << "User " << client.name << " has been registered, real name: " << command.params[3] << std::endl;
#endif
}