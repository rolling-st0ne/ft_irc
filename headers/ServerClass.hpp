/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:55:39 by casteria          #+#    #+#             */
/*   Updated: 2020/12/02 16:20:22 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCLASS_HPP
# define SERVERCLASS_HPP

# include "irc.hpp"

# define SERVER_NAME_LENGTH 63

class		Server
{
	friend class IrcAPI;
private:
	socket_info						sock;
	std::string						name[SERVER_NAME_LENGTH];	
	std::string						password;
	std::vector<Client>				clients;
	std::vector<User>				users;
	std::vector<Server>				servers;
	std::vector<Channel>			channels;
	std::vector<socket_info>		connected_servers;

	timeval							timeout;
	static const int				BUFFER_SIZE = 1024;

	void							initFds(int &, fd_set&, fd_set&);
	void							server_loop();
	void							acceptNewClient();
	void							processClients(fd_set&, fd_set&);
	void							processClientRequest(Client&);
	void							sendDataToClient(Client&);
	void							addClient(Client);
	void							addUser(User); // check with reference
	void							rmClient(Client);
	void							create_server(const int&, const std::string&);
public:
	Server();
	Server(const Server&);
	Server(const int&, const std::string&);
	Server(const char *, const int&, const std::string&);
	~Server();

	// _operators
	Server &operator=(const Server&);

	// _functions
	void							start();
};

#endif