/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcApiClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 23:36:15 by casteria          #+#    #+#             */
/*   Updated: 2020/11/25 21:53:00 by casteria         ###   ########.fr       */
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

typedef void (*process_function)(Server*, Client*, const t_command&);

typedef std::map<std::string, process_function> t_map;

class		IrcAPI
{
private:
    static t_map      commands;


    static t_map            create_map();
    static t_command        parse_query(const std::string&);
    static void             process_query(Server*, Client*, const t_command&);

    // COMMANDS
    static void				pass(Server*, Client*, const t_command&);		
    static void				nick(Server*, Client*, const t_command&);
	static void				user(Server*, Client*, const t_command&);
public:
    static void            run_query(Server*, Client*, const std::string&);

};

// TODO: nick hopcount

#endif