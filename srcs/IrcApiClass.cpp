/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcApiClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:01:13 by gwynton           #+#    #+#             */
/*   Updated: 2020/11/24 19:27:49 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

const std::map<std::string, parse_function> IrcAPI::commands
{
    std::make_pair("NICK", &test_parse)
};

void test_parse(std::string input)
{
    
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
        std::cout << str;
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
    commands.find("NICK")->second("OK");
    //commands["NICK"]("OK");
}