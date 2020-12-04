/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:50:57 by casteria          #+#    #+#             */
/*   Updated: 2020/12/05 02:12:38 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_pass(Server& server, Client& client, const t_command& command)
{
	if (client.is_registered)
	{
		client.response += ":localhost ";
		client.response += ERR_ALREADYREGISTRED;
		client.response += " " + client.name + " :Unauthorized command (already registered)\r\n";
	}
	else
		client.password = command.params[0];

	(void)server;
}
