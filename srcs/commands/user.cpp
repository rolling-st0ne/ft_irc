/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:06:19 by casteria          #+#    #+#             */
/*   Updated: 2020/12/01 04:03:37 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_user(Server& server, Client& client, const t_command& command)
{
	if (client.is_registered)
		throw IrcException(ERR_ALREADYREGISTRED);
	if (command.amount_of_params != 4)
		throw IrcException(ERR_NEEDMOREPARAMS);
	server.users.push_back(User(command.params[0], command.params[1], command.params[2], command.params[3]));
	client.is_registered = true;
#ifdef DEBUG_MODE
	DEBUG_MES("User " << client.name << " has been registered\n")
#endif
	(void)server;
}