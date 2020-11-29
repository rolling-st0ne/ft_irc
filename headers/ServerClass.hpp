/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:55:39 by casteria          #+#    #+#             */
/*   Updated: 2020/11/29 15:19:03 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCLASS_HPP
# define SERVERCLASS_HPP

# include "irc.hpp"

# define SERVER_NAME_LENGTH 63

class		Server : private Client
{
	friend class IrcAPI;
private:
	std::string						name[SERVER_NAME_LENGTH];
	std::string						password;
	std::vector<Client*>			clients;
	std::vector<User*>				users;
	std::vector<Server*>				servers;
	std::vector<Channel>			channels;
	std::vector<socket_info>		connected_servers;

	timeval							timeout;
	static const int				BUFFER_SIZE = 1024;

	void							initFds(int &, fd_set&, fd_set&);
	void							server_loop();
	void							acceptNewClient();
	void							processClients(fd_set &, fd_set&);
	void							processClientRequest(Client *);
	void							sendDataToClient(Client *);
	void							addClient(Client *);
	void							rmClient(Client &);
	void							addUser(Client **);
	void							connectToServer(const socket_info&);
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
	void							setSocket(socket_info);
	socket_info						getSocket() const;
	const std::vector<Client *>		&getClients() const;
	void							start();
};

#endif