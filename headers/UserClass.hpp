/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:15:28 by casteria          #+#    #+#             */
/*   Updated: 2020/11/22 01:24:17 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

class		User : public Client
{
private:
	std::string	nickname[9];
    std::string login;
    std::string password;
    std::vector<t_message> buffer;



};