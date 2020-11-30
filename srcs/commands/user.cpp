/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:06:19 by casteria          #+#    #+#             */
/*   Updated: 2020/11/30 22:16:23 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_user(Server& server, Client& client, const t_command&)
{
    if ((dynamic_cast<User*>(client))->nickname.empty())
		throw IrcException("Command \'USER\' failed");
	(dynamic_cast<User*>(client))->registered = true;
#ifdef DEBUG_MODE
	DEBUG_MES("User " << (dynamic_cast<User*>(client))->nickname << " has been registered\n")
#endif
	(void)server;
}