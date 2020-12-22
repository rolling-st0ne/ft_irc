/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcApiClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:01:13 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/22 21:10:54 by gwynton          ###   ########.fr       */
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
	res["OPER"] = cmd_oper;
	res["MOTD"] = cmd_motd;
	res[RPL_MOTDSTART] = cmd_motd_start;
	res[RPL_MOTD] = cmd_motd_response;
	res[RPL_ENDOFMOTD] = cmd_motd_end;
	res["VERSION"] = cmd_version;
	res[RPL_VERSION] = cmd_version_response;
	res["TIME"] = cmd_time;
	res[RPL_TIME] = cmd_time_response;
	res["INFO"] = cmd_info;
	res[RPL_ENDOFINFO] = cmd_info_end;
	res[RPL_INFO] = cmd_info_response;
	res["ADMIN"] = cmd_admin;
	res[RPL_ADMINME] = cmd_admin_response1;
	res[RPL_ADMINLOC1] = cmd_admin_response2;
	res[RPL_ADMINLOC2] = cmd_admin_response3;
	res[RPL_ADMINEMAIL] = cmd_admin_response4;
	res["STATS"] = cmd_stats;
	res[RPL_ENDOFSTATS] = cmd_stats_end;
	res[RPL_STATSUPTIME] = cmd_stats_uptime;
	res["SQUIT"] = cmd_squit;
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
			//size_t position = query.find_last_of(':');
			size_t position = query.substr(1).find_first_of(':');
			std::string temp = query.substr(position + 1);
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
	client.response += ":" + server.name + " ";
	client.response += numericReply;
	client.response += " " + client.name;
	client.response += " " + textReply;
	client.response += "\r\n";
}
