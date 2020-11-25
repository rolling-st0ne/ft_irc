/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 02:00:11 by casteria          #+#    #+#             */
/*   Updated: 2020/11/25 20:16:23 by casteria         ###   ########.fr       */
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
		else if (argc == 5)
			server = new Server(atoi(argv[1]), argv[2], atoi(argv[3]), argv[4]);
		else
			throw IrcException("Bad amount of argumntes");
		server->start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	delete server;
	return (SUCCESS);
}