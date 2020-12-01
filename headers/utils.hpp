/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:39:39 by gwynton           #+#    #+#             */
/*   Updated: 2020/12/02 02:29:31 by gwynton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "irc.hpp"

std::vector<std::string>	strsplit(const std::string&, char);
bool						getNextQuery(std::string&, std::string&);

#endif
