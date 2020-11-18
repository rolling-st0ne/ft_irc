/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 02:00:11 by casteria          #+#    #+#             */
/*   Updated: 2020/11/18 16:12:16 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "ServerClass.hpp"

int				main(int argc, char **argv)
{
	Server		server;
	try
	{
		(void)argc;
		(void)argv;
		init(argc, argv, server);
		server.start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (SUCCESS);
}