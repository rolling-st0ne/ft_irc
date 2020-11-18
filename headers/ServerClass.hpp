/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:55:39 by casteria          #+#    #+#             */
/*   Updated: 2020/11/18 17:31:22 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCLASS_HPP
# define SERVERCLASS_HPP

# include "irc.hpp"

typedef struct	s_socket_info
{
	int					socket_fd;
	struct sockaddr_in	addr;
}				socket_info;			

class		Server
{
private:
	socket_info						socket;
	std::vector<socket_info>		clients;

	void							server_loop();
public:
	Server();
	Server(const Server&);
	~Server();

	// _operators
	Server &operator=(const Server&);

	// _functions
	void							setSocket(socket_info);
	socket_info						getSocket() const;
	const std::vector<socket_info>	&getClients() const;
	void							addClient(socket_info &client);
	void							start();
};

#endif