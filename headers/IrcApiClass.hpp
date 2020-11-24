/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcApiClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 23:36:15 by casteria          #+#    #+#             */
/*   Updated: 2020/11/24 21:53:56 by gwynton          ###   ########.fr       */
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
public:
    static void            run_query(const std::string&);

};

#endif