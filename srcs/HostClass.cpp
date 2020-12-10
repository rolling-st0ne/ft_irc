/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HostClass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:28:23 by casteria          #+#    #+#             */
/*   Updated: 2020/12/10 19:07:25 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HostClass.hpp"

Host::Host(const std::string servername, const unsigned int hopcount, const unsigned int token, const std::string info)
	:	servername(servername),
		hopcount(hopcount),
		token(token),
		info(info)
{
}

Host::~Host()
{
}