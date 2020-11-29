/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:06:19 by casteria          #+#    #+#             */
/*   Updated: 2020/11/29 15:12:05 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_user(Server* server, Client* client, const t_command&)
{
    if ((dynamic_cast<User*>(client))->nickname.empty())
		throw IrcException("Command \'USER\' failed");
	(dynamic_cast<User*>(client))->registered = true;
	std::cerr << "User " << (dynamic_cast<User*>(client))->nickname << " has been registered" << std::endl;
	(void)server;
}