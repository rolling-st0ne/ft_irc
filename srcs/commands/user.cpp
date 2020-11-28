/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:06:19 by casteria          #+#    #+#             */
/*   Updated: 2020/11/28 18:24:43 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_user(Server* server, Client* client, const t_command&)
{
	std::cerr << "|" << (dynamic_cast<User*>(client))->nickname << "|";
    if ((dynamic_cast<User*>(client))->nickname.empty())
		throw IrcException("Command \'USER\' failed");
	server->addUser(dynamic_cast<User *>(client));
	std::cerr << "User " << (dynamic_cast<User*>(client))->nickname << " has been added" << std::endl;
}