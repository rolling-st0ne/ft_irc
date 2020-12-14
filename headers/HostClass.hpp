/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HostClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:26:51 by casteria          #+#    #+#             */
/*   Updated: 2020/12/15 00:25:47 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOSTCLASS_HPP
# define HOSTCLASS_HPP

# include "irc.hpp"

class Host
{
private:

public:
	std::string		servername;
	unsigned int	hopcount;
	std::string		info;
	Host(const std::string servername, const unsigned int hopcount, const std::string info);
	~Host();

};

#endif