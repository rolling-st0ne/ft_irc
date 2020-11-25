/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcApiClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:01:13 by gwynton           #+#    #+#             */
/*   Updated: 2020/11/26 00:40:15 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

t_map IrcAPI::create_map()
{
	t_map	res;

	res["NICK"] = nick;
    res["PASS"] = pass;
    res["USER"] = user;
	return (res);
}

t_map IrcAPI::commands = create_map();

void IrcAPI::run_query(Server *server, Client *client, const std::string& query)
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
    process_query(server, client, command);
}

t_command IrcAPI::parse_query(const std::string& query)
{
    t_command result;
    std::vector<std::string> after_split = strsplit(query);
	int size = after_split.size();
	int command_index = 0;
    if (size < 1)
    {
        result.command = "BAD";
        return result;
    }
    if (after_split[0][0] == ':')
    {
        result.prefix = after_split[0];
		command_index++;
    }
	if (size > command_index && commands.find(after_split[command_index]) != commands.end())
	{
		result.command = after_split[command_index];
	}
    else
    {
        result.command = "BAD";
    }
	for (int i = 1; i < size - command_index; i++)
	{
		result.params.push_back(after_split[i + command_index]);
	}
    return result;
}

void IrcAPI::process_query(Server *server, Client* client, const t_command& command)
{
    //t_map::iterator it = commands.find(command.command);
    if (command.command != "BAD")
        commands[command.command](server, client, command);
	else
		std::cerr << "Invalid command\n";
//    commands.find("NICK")->second("OK");
}