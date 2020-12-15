/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:41:24 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/15 18:42:38 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

std::vector<std::string> strsplit(const std::string& input, char del)
{
    std::vector<std::string> result;
	std::string temp;
	std::string	buffer;

	if (input[input.size() - 1] == '\r')
		temp = input.substr(0, input.size() - 1);
	else
		temp = input;
	std::istringstream   strstream(temp);

	while (std::getline(strstream, buffer, del))
	{
		if (buffer.empty())
			continue;
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

std::string					getHostName(const sockaddr_in& sock)
{
	std::ostringstream	os;
	std::string			to_return = inet_ntoa(sock.sin_addr);

	to_return += '/';
	os << sock.sin_port;
	to_return += os.str();
	return (to_return);
}

bool						is_registered(const Client& client)
{
	return (client.status != CLIENT && client.status != WAITING_FOR_CONNECTION);
}
