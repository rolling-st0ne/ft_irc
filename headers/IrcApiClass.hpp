/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcApiClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 23:36:15 by casteria          #+#    #+#             */
/*   Updated: 2020/12/06 00:44:06 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCAPICLASS_HPP
# define IRCAPICLASS_HPP

# include "irc.hpp"

typedef struct  s_command
{
	bool valid;
    std::string prefix;
    std::string command;
    std::vector<std::string> params;
    unsigned short int  amount_of_params;
    short int				belongs_to;
}               t_command;

#define COMMANDS_PARAM_LIST Server&, Client&, const t_command&

typedef void (*process_function)(COMMANDS_PARAM_LIST);

typedef std::map<std::string, process_function> t_map;

class		IrcAPI
{
private:
    static t_map      commands;

    static t_map            create_map();
    static t_command        parse_query(const std::string&);
    static void             process_query(COMMANDS_PARAM_LIST);
    static void             sendReply(const std::string&, const std::string&, Client&);

    // COMMANDS
    static void				cmd_pass(COMMANDS_PARAM_LIST);	


    static void				cmd_nick(COMMANDS_PARAM_LIST);
	static bool				nick_in_use(Server& server, const std::string& nickname);

	static void				cmd_user(COMMANDS_PARAM_LIST);

	static void				cmd_join(COMMANDS_PARAM_LIST);
	static Channel*			channel_by_name(Server&, const std::string&);

	static void				cmd_part(COMMANDS_PARAM_LIST);

	static void				cmd_topic(COMMANDS_PARAM_LIST);

	static void				cmd_privmsg(COMMANDS_PARAM_LIST);

    static void             cmd_server(COMMANDS_PARAM_LIST);

	static void				cmd_quit(COMMANDS_PARAM_LIST);

public:
    static void				run_query(Server&, Client&, const std::string&);
	static std::string		user_by_nick(Server&, const std::string&);
	static void				sendToUser(Server&, std::string&, std::string&);

};

// TODO: nick hopcount

#endif