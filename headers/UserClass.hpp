/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:15:28 by casteria          #+#    #+#             */
/*   Updated: 2020/11/24 18:40:33 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERCLASS_HPP
# define USERCLASS_HPP

# include "irc.hpp"

class		User : public Client
{
private:
	std::string	nickname[9];
    std::vector<t_message> buffer;
public:
    User(const Client &);
};

#endif