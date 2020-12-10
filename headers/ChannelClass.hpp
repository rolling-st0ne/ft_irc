/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelClass.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:43:31 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/11 01:28:54 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELCLASS_HPP
# define CHANNELCLASS_HPP

#include "irc.hpp"

class Channel
{

private:

public:
	std::string					name;
	std::string					creator;
	std::vector<std::string>	members;
	std::vector<std::string>	operators;
	std::string					topic;

	Channel(std::string, std::string);
	bool						addUser(std::string);
	void						removeUser(std::string);
	void						removeOperator(std::string);
};

#endif