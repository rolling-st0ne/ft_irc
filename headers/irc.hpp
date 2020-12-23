/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 02:02:32 by casteria          #+#    #+#             */
/*   Updated: 2020/12/23 20:51:19 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

// __classes declarations
class Host;
class Server;
class IrcAPI;
class Client;
class User;
class Channel;

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
# include <iterator>
# include <sys/time.h>
# include <sstream>
# include <cstdlib>
# include <csignal>

// _networking
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <openssl/ssl.h>
# include <openssl/err.h>

// ___structs
typedef struct	s_socket_info
{
	int					socket_fd;
	struct sockaddr_in	addr;
	socklen_t			socklen;
}				socket_info;

// ___our classes
# include "Errors.hpp"
# include "Responses.hpp"
# include "ClientClass.hpp"
# include "ServerClass.hpp"
# include "UserClass.hpp"
# include "ChannelClass.hpp"
# include "ExceptionsClasses.hpp"
# include "IrcApiClass.hpp"
# include "HostClass.hpp"
# include "utils.hpp"

// ___defines
# define SUCCESS 0
# define FAIL -1
# define SERVER_RUNS 1
# define DEBUG_MES(str) std::cerr << "\x1b[1;31m" << str << "\x1b[0m";

# define CLIENT 0
# define USER 1
# define SERVER 2
# define WAITING_FOR_CONNECTION 3

// ___constants
const int QUEUE_LEN_MAX = 16;

// ___functions

#endif