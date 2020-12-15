/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserClass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:15:11 by casteria          #+#    #+#             */
/*   Updated: 2020/12/16 00:23:20 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserClass.hpp"

User::User(const Client &other)
	:	nickname(other.name)
{
}

User::User(const std::string& nickname, const std::string& username, const std::string& hostname, \
        const std::string& servername, const std::string& realname)
	:	nickname(nickname),
		username(username),
		hostname(hostname),
		servername(servername),
		realname(realname),
		hopcount(0)
{
}
