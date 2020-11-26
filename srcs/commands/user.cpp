/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:06:19 by casteria          #+#    #+#             */
/*   Updated: 2020/11/26 19:08:19 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_user(Server* server, Client* client, const t_command&)
{
    if (!client->authenticated || client->nickname.empty())
		throw IrcException("Command \'USER\' failed");
	server->addUser(client);
	std::cerr << "User " << client->nickname << " has been added" << std::endl;
}