/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:50:57 by casteria          #+#    #+#             */
/*   Updated: 2020/12/10 19:08:11 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_pass(Server& server, Client& client, const t_command& command)
{
	if (client.status)
		sendReply(ERR_ALREADYREGISTRED, ":Unauthorized command (already registered)", client);
	else if (command.amount_of_params < 1)
		sendReply(ERR_NEEDMOREPARAMS, "PASS :Not enough parameters", client);
	else
		client.password = command.params[0];

	(void)server;
}
