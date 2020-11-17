/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExceptionsClasses.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <casteria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:27:53 by casteria          #+#    #+#             */
/*   Updated: 2020/11/17 20:37:46 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONCLASSES_HPP
# define EXCEPTIONCLASSES_HPP

# include <exception>
# include <string>
# include <iostream>
# include <errno.h>

class IrcException : public std::exception
{
private:
	std::string		err_message;
public:
	IrcException(const std::string &str)
	{
		err_message += "Error: " + str;
	}
	IrcException(const int &err)
	{
		err_message += "Error: " + std::string(strerror(err));
	}
	virtual const char* what() const throw()
	{
		return (err_message.c_str());
	}
	~IrcException() throw () { return ; }
};

#endif