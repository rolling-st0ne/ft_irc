/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:50:57 by casteria          #+#    #+#             */
/*   Updated: 2020/12/15 18:44:07 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_pass(Server& server, Client& client, const t_command& command)
{
	if (is_registered(client))
		sendReply(server, ERR_ALREADYREGISTRED, ":Unauthorized command (already registered)", client);
	else if (command.amount_of_params < 1)
		sendReply(server, ERR_NEEDMOREPARAMS, "PASS :Not enough parameters", client);
	else
		client.password = command.params[0];
}
