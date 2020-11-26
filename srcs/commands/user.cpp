/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:06:19 by casteria          #+#    #+#             */
/*   Updated: 2020/11/26 04:00:44 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::user(Server* server, Client* client, const t_command&)
{
    if (!client->authenticated || client->nickname.empty())
		throw IrcException("Command \'USER\' failed");
	server->addUser(client);
	std::cerr << "User " << client->nickname << " has been added" << std::endl;
}