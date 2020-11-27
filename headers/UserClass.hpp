/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:15:28 by casteria          #+#    #+#             */
/*   Updated: 2020/11/27 21:40:10 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERCLASS_HPP
# define USERCLASS_HPP

# include "irc.hpp"

# define CLIENT_NAME_LENGTH 9

class		User : private Client
{
public:
    std::string		nickname;
    bool			authenticated;
	bool			registered;
    std::vector<t_message> buffer;
public:
    User(const Client &);
};

#endif