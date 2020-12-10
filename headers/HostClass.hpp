/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HostClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:26:51 by casteria          #+#    #+#             */
/*   Updated: 2020/12/10 19:07:05 by casteria         ###   ########.fr       */
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
	unsigned int	token;
	std::string		info;
	Host(const std::string servername, const unsigned int hopcount, const unsigned int token, const std::string info);
	~Host();

};

#endif