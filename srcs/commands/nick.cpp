/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:10:11 by casteria          #+#    #+#             */
/*   Updated: 2020/11/27 21:06:46 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_nick(Server *server, Client* client, const t_command& command)
{
    if (command.params.size() != 1 || command.params[0].size() > 9)
        throw IrcException("nick command is bad");
    (reinterpret_cast<User *>(client))->nickname = command.params[0];
    (void)server;
}