/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcApiClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:01:13 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/18 14:43:07 by gwynton          ###   ########.fr       */
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
	res["JOIN"] = cmd_join;
	res["PRIVMSG"] = cmd_privmsg;
	res["PART"] = cmd_part;
	res["TOPIC"] = cmd_topic;
	res["QUIT"] = cmd_quit;
	res["NOTICE"] = cmd_notice;
	res["MODE"] = cmd_mode;
	res["KICK"] = cmd_kick;
	res["NJOIN"] = cmd_njoin;
	res["KILL"] = cmd_kill;
	return (res);
}

t_map IrcAPI::commands = create_map();

void IrcAPI::run_query(Server &server, Client& client, const std::string& query)
{
    t_command command;
	std::string message;
	std::string currentQuery;
    try
    {
		if (!client.input.empty())
		{
			message = client.input;
			client.input = "";
		}
		message += query;
		while (getNextQuery(message, currentQuery))
		{
			//std::cerr << "Current query: " << currentQuery << std::endl;
			command = parse_query(currentQuery);
			process_query(server, client, command);
		}
		client.input = message;
    }
    catch (const std::exception& ex)
    {
        client.response = std::string(ex.what());
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
        result.command = "<Empty>";
		result.valid = false;
        return result;
    }
    if (after_split[0][0] == ':')
    {
        result.prefix = after_split[0];
		command_index++;
    }
	if (size > command_index)
	{
		result.command = after_split[command_index];
		if (commands.find(after_split[command_index]) != commands.end())
			result.valid = true;
		else
			result.valid = false;
	}
    else
    {
        result.command = "<Empty>";
		result.valid = false;
        return result;
    }
	for (int i = 1; i < size - command_index; i++)
	{
		if (after_split[i + command_index][0] == ':')
		{
			size_t position = query.find_last_of(':');
			std::string temp = query.substr(position);
			result.params.push_back(temp);
			break;
		}
		result.params.push_back(after_split[i + command_index]);
	}
    result.amount_of_params = result.params.size();
    return result;
}

void IrcAPI::process_query(Server &server, Client &client, const t_command& command)
{
	if (!command.valid && atoi(command.command.c_str()) < 100)
		sendReply(server, ERR_UNKNOWNCOMMAND, command.command + " :Unknown command", client);
	else if (command.valid)
    	commands[command.command](server, client, command);
}

void IrcAPI::sendReply(Server& server, const std::string& numericReply, const std::string& textReply, Client& client)
{
	client.response += ":" + server.name + " "; //To be replaced with server name
	client.response += numericReply;
	client.response += " " + client.name;
	client.response += " " + textReply;
	client.response += "\r\n";
}
