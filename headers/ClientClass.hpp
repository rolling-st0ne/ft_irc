/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:18:18 by casteria          #+#    #+#             */
/*   Updated: 2020/11/30 21:58:19 by casteria         ###   ########.fr       */
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
		
		void 		clear();
		bool 		isEmpty() const;
	};
	Client();
	Client(const Client&);
	virtual ~Client();
	Buffer			buffer;
};

#endif