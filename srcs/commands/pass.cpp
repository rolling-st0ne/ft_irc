/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:50:57 by casteria          #+#    #+#             */
/*   Updated: 2020/11/29 15:34:58 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_pass(Server *server, Client* client, const t_command& command)
{
//	std::cerr << "auth: " << dynamic_cast<User*>(client)->authenticated << std::endl;
	if (command.params.size() != 1 || command.params[0] != server->password)
		throw (IrcException("The password is incorrect"));
	dynamic_cast<User *>(client)->authenticated = true;
	(void)server;
}
