/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:55:39 by casteria          #+#    #+#             */
/*   Updated: 2020/11/22 01:24:05 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCLASS_HPP
# define SERVERCLASS_HPP

# include "irc.hpp"			

class		Server // to establish connetion between servers
{
private:
	socket_info						socket;
	std::string						password;
	std::vector<Client>				clients;
	std::vector<User>				users;

	timeval							timeout;
	static const int				BUFFER_SIZE = 1024;

	void							initFds(int &, fd_set&, fd_set&);
	void							server_loop();
	void							acceptNewClient();
	void							processClients(fd_set &, fd_set&);
	void							processClientRequest(const int&);
	void							sendDataToClient(const int&);
	void							addClient(Client &);
	t_message						parseRequest(const char *);
public:
	Server();
	Server(const Server&);
	~Server();

	// _operators
	Server &operator=(const Server&);

	// _functions
	void							setSocket(socket_info);
	socket_info						getSocket() const;
	const std::vector<Client>		&getClients() const;
	void							start();
};

#endif