/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserClass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:15:11 by casteria          #+#    #+#             */
/*   Updated: 2020/12/01 03:12:27 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserClass.hpp"

User::User(const Client &other)
	:	nickname(other.name)
{
}

User::User(const std::string& nickname, const std::string& hostname, \
        const std::string& servername, const std::string& realname)
	:	nickname(nickname),
		hostname(hostname),
		servername(servername),
		realname(realname)
{
}