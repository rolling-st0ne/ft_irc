/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:50:57 by casteria          #+#    #+#             */
/*   Updated: 2020/11/28 18:27:53 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_pass(Server *server, Client* client, const t_command& command)
{
	if (command.params.size() != 1 || command.params[0] != server->password)
		throw (IrcException("The password is incorrect"));
	std::cerr << dynamic_cast<User *>(&server->clients[0]) << std::endl;
	(dynamic_cast<User *>(client))->authenticated = true;
	(void)client;
}
