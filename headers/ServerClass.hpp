/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:55:39 by casteria          #+#    #+#             */
/*   Updated: 2020/11/20 14:37:48 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCLASS_HPP
# define SERVERCLASS_HPP

# include "irc.hpp"

typedef struct	s_socket_info
{
	int					socket_fd;
	struct sockaddr_in	addr;
	socklen_t			socklen;
}				socket_info;			

class		Server
{
private:
	socket_info						socket;
	std::vector<socket_info>		clients;

	timeval							timeout;

	void							initFds(int &, fd_set&, fd_set&);
	void							server_loop();
	void							acceptNewClient();
	void							processClients(fd_set &, fd_set&);
	void							receiveDataFromClient();
	void							sendDataToClient();
	void							addClient(socket_info client);
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
	void							start();
};

#endif