/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 02:00:11 by casteria          #+#    #+#             */
/*   Updated: 2020/11/27 00:41:18 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "ServerClass.hpp"

int				main(int argc, char **argv)
{
	Server *server;
	
	try
	{
		if (argc == 3)
			server = new Server(atoi(argv[1]), argv[2]);
		else if (argc == 4)
			server = new Server(argv[1], atoi(argv[2]), argv[3]);
		else
			throw IrcException("Bad amount of arguments");
		server->start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	delete server;
	return (SUCCESS);
}