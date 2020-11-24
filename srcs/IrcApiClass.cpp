/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcApiClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:01:13 by gwynton           #+#    #+#             */
/*   Updated: 2020/11/25 01:20:05 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

t_map IrcAPI::create_map()
{
	t_map	res;

	res["NICK"] = test_parse;
	return (res);
}

t_map IrcAPI::commands = create_map();

void test_parse(std::string input)
{
    //(void)input;
	std::cerr << input;
}

void IrcAPI::run_query(const std::string& query)
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
    process_query(command);
}

t_command IrcAPI::parse_query(const std::string& query)
{
    t_command result;
    std::vector<std::string> after_split = strsplit(query, ' ');
    if (after_split.size() < 2)
    {
        result.command = "BAD";
        return result;
    }
    result.prefix = after_split[0];
    result.command = after_split[1];
    return result;
}

void IrcAPI::process_query(const t_command& command)
{
	commands["NICK"]("OK");
//    commands.find("NICK")->second("OK");
    (void)command;
}