/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:41:24 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/20 10:08:35 by gwynton          ###   ########.fr       */
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
	os << ntohs(sock.sin_port);
	to_return += os.str();
	return (to_return);
}

bool						is_registered(const Client& client)
{
	return (client.status != CLIENT && client.status != WAITING_FOR_CONNECTION);
}

std::string					toString(const int& val)
{
	std::stringstream is;
	is << val;
	return (is.str());
}

bool						compareLower(const std::string& a, const std::string& b)
{
	size_t size = a.size();
	if (size != b.size())
		return false;
	for (size_t i = 0; i < size; i++)
	{
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	}
	return true;
}
