/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 02:02:32 by casteria          #+#    #+#             */
/*   Updated: 2020/11/20 17:33:14 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

// __classes declarations
class Server;

// ___standart includes
# include <iostream>
# include <string>
# include <vector>
# include <list>
# include <queue>
# include <stack>
# include <map>
# include <algorithm>

# include <cerrno>
# include <cstring>
# include <algorithm>
# include <iterator>
# include <sys/time.h>
# include <sstream>

// _networking
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <fcntl.h>

// ___structs
typedef struct	s_socket_info
{
	int					socket_fd;
	struct sockaddr_in	addr;
	socklen_t			socklen;
}				socket_info;

typedef struct	s_message
{
	std::string	command;
	std::string content;
}				t_message;

typedef struct	s_user
{
	socket_info *socket;
	std::string	name;
}				t_user;

// ___our classes
# include "ServerClass.hpp"
# include "ExceptionsClasses.hpp"

// ___defines
# define SUCCESS 0
# define FAIL -1
# define SERVER_RUNS 1

// ___constants
const int QUEUE_LEN_MAX = 16;

// ___functions
void					init(int argc, char **argv, Server&);
void					createOwnNetwork(char **argv, Server&);
void					joinNetwork(char **argv, Server&);

#endif