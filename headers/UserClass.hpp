/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:15:28 by casteria          #+#    #+#             */
/*   Updated: 2020/12/18 17:26:52 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERCLASS_HPP
# define USERCLASS_HPP

# include "irc.hpp"

# define CLIENT_NAME_LENGTH 9

class		User
{
public:
    std::string		nickname;
	std::string		username;
    std::string     hostname;
    std::string     servername;
    std::string     realname;
    unsigned int	hopcount;
    bool            ircOp;
public:
    User(const Client &);
    User(const std::string& nickname, const std::string& username, const std::string& hostname, \
        const std::string& servername, const std::string& realname);
};

#endif