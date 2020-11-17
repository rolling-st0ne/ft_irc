/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExceptionsClasses.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:27:53 by casteria          #+#    #+#             */
/*   Updated: 2020/11/17 12:15:37 by casteria         ###   ########.fr       */
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

class SocketCreateFailedException : public std::exception
{
	virtual const char *what() const throw()
	{
		return ("Couldn't create socket");
	}
};

class BadSockAddrException : public std::exception
{
	virtual const char *what() const throw()
	{
		return ("Bad port adress");
	}
};

class ListenException : public std::exception
{
	virtual const char *what() const throw()
	{
		return ("Listen failed");
	}
};

#endif