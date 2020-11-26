/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:55:39 by casteria          #+#    #+#             */
/*   Updated: 2020/11/26 21:37:14 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCLASS_HPP
# define SERVERCLASS_HPP

# include "irc.hpp"

class		Server // to establish connetion between servers
{
	friend class IrcAPI;
private:
	socket_info						server_socket;
	std::string						password;
	std::vector<Client>				clients;
	std::vector<Client*>			users;
	std::vector<Channel>			channels;
	std::vector<socket_info>		connected_servers;

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
	void							addUser(Client *);
	void							connectToServer(const socket_info&);
	void							create_server(const int&, const std::string&);
public:
	Server();
	Server(const Server&);
	Server(const int&, const std::string&);
	Server(const int&, const std::string&, const int&, const std::string&);
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