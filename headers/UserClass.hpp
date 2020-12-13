/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:15:28 by casteria          #+#    #+#             */
/*   Updated: 2020/12/13 09:20:23 by gwynton          ###   ########.fr       */
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
    std::string     hostname;
    std::string     servername;
    std::string     realname;
public:
    User(const Client &);
    User(const std::string& nickname, const std::string& hostname, \
        const std::string& servername, const std::string& realname);
};

#endif