/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 01:55:39 by casteria          #+#    #+#             */
/*   Updated: 2020/12/22 07:56:20 by gwynton          ###   ########.fr       */
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
	socket_info						ssl_sock;
	std::string						name;	
	std::string						password;
	std::vector<Client>				clients;
	std::vector<User>				users;
	std::vector<Host>				hosts;
	std::vector<Channel>			channels;
	std::vector<std::string>		connected_servers;
	SSL_CTX							*ssl_server_ctx;
	SSL_CTX*						ssl_client_ctx;
	int								uplink;

	timeval							timeout;
	static const int				BUFFER_SIZE = 4096;

	void							initFds(int &, fd_set&, fd_set&);
	void							server_loop();
	void							acceptNewClient(fd_set&);
	void							processClients(fd_set&, fd_set&);
	void							processClientRequest(Client&);
	void							sendDataToClient(Client&);
	int								recvMsg(Client&, void *, int);
	static void						sendMessage(Client&, std::string);
	void							addClient(Client);
	void							addUser(User);
	void							addHost(Host);
	void							rmClient(Client);
	void							create_socket(const int&, socket_info&);
	void							create_server(const int&, const std::string&);
	void							connect_server(const std::string&, const std::string&, const std::string);
	void							propagate(const std::string&, const std::string&);
	std::string						getTimeString();

	SSL_CTX*						InitCTX(int);
	void							initSSL(Client&, SSL_CTX*);
	void							LoadCertificates(SSL_CTX*, const char*, const char*);
public:
	Server();
	Server(const Server&);
	Server(const int&, const std::string&);
	Server(const char *, const int&, const std::string&);
	~Server(); // add it

	// _operators
	Server &operator=(const Server&);

	// _functions
	void							start();
};

#endif