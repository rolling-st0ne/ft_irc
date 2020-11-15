/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:55:39 by casteria          #+#    #+#             */
/*   Updated: 2020/11/16 02:00:45 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCLASS_HPP
# define SERVERCLASS_HPP

class Server
{
private:
	
public:
	Server();
	Server(const Server&);
	~Server();

	Server &operator=(const Server&);
};

#endif