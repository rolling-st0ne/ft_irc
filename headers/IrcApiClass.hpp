/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcApiClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 23:36:15 by casteria          #+#    #+#             */
/*   Updated: 2020/11/25 18:11:58 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCAPICLASS_HPP
# define IRCAPICLASS_HPP

# include "irc.hpp"

typedef struct  s_command
{
    std::string prefix;
    std::string command;
    std::vector<std::string> params;
}               t_command;

typedef void (*parse_function)(std::string);

typedef std::map<std::string, parse_function> t_map;

void test_parse(std::string);

class		IrcAPI
{
private:
    static t_map      commands;


    static t_map            create_map();
    static t_command        parse_query(const std::string&);
    static void             process_query(const t_command&);

    // COMMANDS
    void                    nick(void);
public:
    static void            run_query(const std::string&);

};

#endif