/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:55:39 by casteria          #+#    #+#             */
/*   Updated: 2020/11/24 18:08:01 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCLASS_HPP
# define SERVERCLASS_HPP

# include "irc.hpp"			

class		Server // to establish connetion between servers
{
	friend class IrcAPI;
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
	void							processClientRequest(Client &);
	void							sendDataToClient(Client &);
	void							addClient(Client &);
	void							rmClient(Client &);
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