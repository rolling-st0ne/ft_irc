/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:10:11 by casteria          #+#    #+#             */
/*   Updated: 2020/11/29 15:28:02 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcApiClass.hpp"

void        IrcAPI::cmd_nick(Server *server, Client* client, const t_command& command)
{
    if (command.params.size() != 1 || command.params[0].size() > 9)
        throw IrcException("nick command is bad");
    (dynamic_cast<User *>(client))->nickname = command.params[0];
    (void)server;
}