/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:50:57 by casteria          #+#    #+#             */
/*   Updated: 2020/11/26 19:08:25 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_pass(Server *server, Client* client, const t_command& command)
{
	if (command.params.size() != 1 || command.params[0] != server->password)
		throw (IrcException("The password is incorrect"));
    client->authenticated = true;
}
