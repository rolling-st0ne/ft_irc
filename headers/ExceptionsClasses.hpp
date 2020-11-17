/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExceptionsClasses.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:27:53 by casteria          #+#    #+#             */
/*   Updated: 2020/11/17 10:40:41 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONCLASSES_HPP
# define EXCEPTIONCLASSES_HPP

# include <exception>

class BadArgsException : public std::exception
{
	virtual const char *what() const throw()
	{
		return ("Bad amount of arguments");
	}
};

#endif