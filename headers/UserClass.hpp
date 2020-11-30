/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:15:28 by casteria          #+#    #+#             */
/*   Updated: 2020/12/01 01:03:41 by casteria         ###   ########.fr       */
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
    std::vector<t_message> buffer;
public:
    User(const Client &);
};

#endif