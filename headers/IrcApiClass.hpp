/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcApiClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 23:36:15 by casteria          #+#    #+#             */
/*   Updated: 2020/11/26 21:38:08 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCAPICLASS_HPP
# define IRCAPICLASS_HPP

# include "irc.hpp"

typedef		enum CMD_TYPE
{
	SERVER,
	USER,
	CHANNEL
};

typedef struct  s_command
{
    std::string prefix;
    std::string command;
    std::vector<std::string> params;
    short int				belongs_to;
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
    static void				cmd_pass(Server*, Client*, const t_command&);		
    static void				cmd_nick(Server*, Client*, const t_command&);
	static void				cmd_user(Server*, Client*, const t_command&);
    static void             cmd_server(Server *, Client*, const t_command&);
public:
    static void            run_query(Server*, Client*, const std::string&);

};

// TODO: nick hopcount

#endif