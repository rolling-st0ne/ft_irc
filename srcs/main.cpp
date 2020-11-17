/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 02:00:11 by casteria          #+#    #+#             */
/*   Updated: 2020/11/17 10:46:30 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int				main(int argc, char **argv)
{
	Server		server;
	try
	{
		(void)argc;
		(void)argv;
		init(argc, argv, server);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (SUCCESS);
}