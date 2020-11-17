/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 08:40:36 by casteria          #+#    #+#             */
/*   Updated: 2020/11/17 20:26:28 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void					init(int argc, char **argv, Server& serv)
{
	if (argc == 3)
		createOwnNetwork(argv, serv);
	else if (argc == 4)
		joinNetwork(argv, serv);
	else
		throw IrcException("Bad amount of arguments");
}