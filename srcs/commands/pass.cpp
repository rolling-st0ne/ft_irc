/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:50:57 by casteria          #+#    #+#             */
/*   Updated: 2020/12/05 10:57:25 by gwynton          ###   ########.fr       */
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
	else if (command.amount_of_params < 1)
	{
		client.response += ":localhost ";
		client.response += ERR_NEEDMOREPARAMS;
		client.response += " " + client.name + " USER :Not enough parameters\r\n";
	}
	else
		client.password = command.params[0];

	(void)server;
}
