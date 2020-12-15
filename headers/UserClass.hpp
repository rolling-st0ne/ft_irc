/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:15:28 by casteria          #+#    #+#             */
/*   Updated: 2020/12/16 00:24:43 by casteria         ###   ########.fr       */
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
public:
    User(const Client &);
    User(const std::string& nickname, const std::string& username, const std::string& hostname, \
        const std::string& servername, const std::string& realname);
};

#endif