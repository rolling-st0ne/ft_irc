/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:41:24 by gwynton           #+#    #+#             */
/*   Updated: 2020/11/26 22:29:47 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

std::vector<std::string> strsplit(const std::string& input, char del)
{
    std::vector<std::string> result;
	std::string temp = input.substr(0, input.size() - 1);
	std::istringstream   strstream(temp);
	std::string	buffer;

	while (std::getline(strstream, buffer, del))
	{
		result.push_back(buffer);
	}
	return (result);
}