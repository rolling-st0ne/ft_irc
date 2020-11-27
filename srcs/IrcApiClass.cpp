/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcApiClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:01:13 by gwynton           #+#    #+#             */
/*   Updated: 2020/11/28 00:00:09 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

t_map IrcAPI::create_map()
{
	t_map	res;

	res["NICK"] = cmd_nick;
    res["PASS"] = cmd_pass;
    res["USER"] = cmd_user;
    res["SERVER"] = cmd_server;
	return (res);
}

t_map IrcAPI::commands = create_map();

void IrcAPI::run_query(Server *server, Client *client, const std::string& query)
{
    t_command command;
    try
    {
        command = parse_query(query);
        process_query(server, client, command);
    }
    catch (const std::exception& ex)
    {
        client->buffer.response = std::string(ex.what()).append("\n");
    }
}

t_command IrcAPI::parse_query(const std::string& query)
{
    t_command result;
    std::vector<std::string> after_split = strsplit(query, ' ');
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
	if (command.command == "BAD")
		throw IrcException("Invalid command");
	if (command.command != "SERVER")
	{
		size_t i = 0;
		if (dynamic_cast<User*>(client))
		{
			for (i = 0; i < server->users.size(); i++)
			{
				if (server->users[i].nickname == (dynamic_cast<User *>(client))->nickname)
					break;
			}
			if (i == server->users.size())
				server->addClient(client);
		}
	}
	else; // to add server if needed
    commands[command.command](server, client, command);
}