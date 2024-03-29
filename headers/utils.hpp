/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:39:39 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/24 01:28:55 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "irc.hpp"

std::vector<std::string>	strsplit(const std::string&, char);
bool						getNextQuery(std::string&, std::string&);
std::string					getHostName(const sockaddr_in&);
bool						is_registered(const Client&);
std::string					toString(const int&);
bool                        compareLower(const std::string&, const std::string&);
//void						sigint_handler(int);

#endif
