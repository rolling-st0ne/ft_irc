/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:06:19 by casteria          #+#    #+#             */
/*   Updated: 2020/11/27 21:10:52 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_user(Server* server, Client* client, const t_command&)
{
    if (!(dynamic_cast<User *>(client))->authenticated || (dynamic_cast<User*>(client))->nickname.empty())
		throw IrcException("Command \'USER\' failed");
	server->addUser((dynamic_cast<User *>(client)));
	std::cerr << "User " << (dynamic_cast<User*>(client))->nickname << " has been added" << std::endl;
}