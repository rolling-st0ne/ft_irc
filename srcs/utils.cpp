/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:41:24 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/02 02:27:11 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

std::vector<std::string> strsplit(const std::string& input, char del)
{
    std::vector<std::string> result;
	std::string temp;

	if (input[input.size() - 1] == '\r')
		temp = input.substr(0, input.size() - 1);
	else
		temp = input;
	std::istringstream   strstream(temp);
	std::string	buffer;

	while (std::getline(strstream, buffer, del))
	{
		result.push_back(buffer);
	}
	return (result);
}

bool getNextQuery(std::string& message, std::string& query)
{
	size_t position = message.find('\n');
	if (position == std::string::npos)
		return false;
	query = message.substr(0, position);
	message = message.substr(position + 1);
	return true;
}