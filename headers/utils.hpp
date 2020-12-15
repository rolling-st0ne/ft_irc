/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:39:39 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/15 18:58:30 by casteria         ###   ########.fr       */
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

#endif
