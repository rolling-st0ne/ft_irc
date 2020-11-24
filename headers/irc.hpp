/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 02:02:32 by casteria          #+#    #+#             */
/*   Updated: 2020/11/24 17:39:16 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

// __classes declarations
class Server;
class IrcAPI;
class Client;
class User;

// ___standard includes
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

typedef struct	s_message // to_delete
{
	std::string	command;
	std::string content;
}				t_message;

// ___our classes
# include "ServerClass.hpp"
# include "ClientClass.hpp"
# include "UserClass.hpp"
# include "ExceptionsClasses.hpp"
# include "IrcApiClass.hpp"
# include "utils.hpp"

// ___defines
# define SUCCESS 0
# define FAIL -1
# define SERVER_RUNS 1
# define DEBUG_MODE
# define DEBUG_MES(str) std::cout << "\x1b[1;31m" << str << "\x1b[0m";

// ___constants
const int QUEUE_LEN_MAX = 16;

// ___functions
void					init(int argc, char **argv, Server&);
void					createOwnNetwork(char **argv, Server&);
void					joinNetwork(char **argv, Server&);

#endif