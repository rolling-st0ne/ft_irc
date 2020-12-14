/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HostClass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:28:23 by casteria          #+#    #+#             */
/*   Updated: 2020/12/15 00:25:40 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HostClass.hpp"

Host::Host(const std::string servername, const unsigned int hopcount, const std::string info)
	:	servername(servername),
		hopcount(hopcount),
		info(info)
{
}

Host::~Host()
{
}