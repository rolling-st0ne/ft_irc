/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:50:57 by casteria          #+#    #+#             */
/*   Updated: 2020/12/01 01:04:17 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_pass(Server& server, Client& client, const t_command& command)
{
	if (client.is_registered)
		throw IrcException(ERR_ALREADYREGISTRED);
	client.password = command.params[0];

	(void)server;
}
