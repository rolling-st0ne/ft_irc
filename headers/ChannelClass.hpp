/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelClass.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:43:31 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/02 06:57:03 by gwynton          ###   ########.fr       */
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
	std::string					topic;

	Channel(std::string, std::string);
	bool						addUser(std::string);
};

#endif