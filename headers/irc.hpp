/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 02:02:32 by casteria          #+#    #+#             */
/*   Updated: 2020/11/18 22:05:52 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

// __classes
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
# include <algorithm>
# include <iterator>

// _networking
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/select.h>

// ___our classes
# include "ServerClass.hpp"
# include "ExceptionsClasses.hpp"

// ___defines
# define SUCCESS 0
# define FAIL -1

// ___constants
const int QUEUE_LEN_MAX = 16;

// ___functions
void					init(int argc, char **argv, Server&);
void					createOwnNetwork(char **argv, Server&);
void					joinNetwork(char **argv, Server&);

#endif