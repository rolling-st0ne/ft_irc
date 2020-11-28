/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:10:11 by casteria          #+#    #+#             */
/*   Updated: 2020/11/28 18:14:59 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_nick(Server *server, Client* client, const t_command& command)
{
    if (command.params.size() != 1 || command.params[0].size() > 9)
        throw IrcException("nick command is bad");
    (static_cast<User *>(client))->nickname = command.params[0];
    (void)server;
}