/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcApiClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:01:13 by gwynton           #+#    #+#             */
/*   Updated: 2020/11/25 20:42:43 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

t_map IrcAPI::create_map()
{
	t_map	res;

	res["NICK"] = nick;
	return (res);
}

t_map IrcAPI::commands = create_map();

void IrcAPI::run_query(Server *server, const std::string& query)
{
    t_command command;
    try
    {
        command = parse_query(query);
    }
    catch (const char* str)
    {
        std::cerr << str;
    }
    process_query(server, command);
}

t_command IrcAPI::parse_query(const std::string& query)
{
    t_command result;
    std::vector<std::string> after_split = strsplit(query);
    if (after_split.size() < 2)
    {
        result.command = "BAD";
        return result;
    }
    if (after_split[0][0] == ':')
    {
        result.prefix = after_split[0];
        result.command = after_split[1];
    }
    else
    {
        result.command = after_split[0];   
    }
    return result;
}

void IrcAPI::process_query(Server *server, const t_command& command)
{
    t_map::iterator it = commands.find(command.command);
    if (it != commands.end())
        commands[command.command](server, command);
//    commands.find("NICK")->second("OK");
    (void)command;
}