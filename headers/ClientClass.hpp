/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:18:18 by casteria          #+#    #+#             */
/*   Updated: 2020/12/02 01:07:33 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTCLASS_HPP
# define CLIENTCLASS_HPP

# include "irc.hpp"

class		Client
{
public:
	socket_info		sock;
	std::string		name;
	std::string		password;
	bool			is_registered;
	class	Buffer ////////////// ugly
	{
	public:
		std::string	response;
		std::string	input;
		void 		clear();
		bool 		isEmpty() const;
	};
	Client();
	Client(const Client&);
	virtual ~Client();
	Buffer			buffer;
};

#endif