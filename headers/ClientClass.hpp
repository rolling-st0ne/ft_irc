/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:18:18 by casteria          #+#    #+#             */
/*   Updated: 2020/11/25 22:01:23 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTCLASS_HPP
# define CLIENTCLASS_HPP

# include "irc.hpp"

class		Client
{
public:
	socket_info		sock;
	bool			authenticated;
	std::string		nickname;
	short int		status;					// make enum
	class	Buffer ////////////// ugly
	{
	public:
		t_message	received;
		std::string	response;
		
		void 		clear();
		bool 		isEmpty() const;
	};
	Client();
	Buffer			buffer;
};

#endif