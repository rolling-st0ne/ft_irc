/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   njoin.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 11:59:32 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/16 02:26:18 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void            IrcAPI::cmd_njoin(Server& server, Client& client, const t_command& command)
{
	if (client.status == USER)
		return ;
	if (command.amount_of_params < 2)
	{
		sendReply(server, ERR_NEEDMOREPARAMS, "NJOIN :Not enough parameters", client);
		return ;
	}
}