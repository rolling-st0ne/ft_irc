/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExceptionsClasses.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:27:53 by casteria          #+#    #+#             */
/*   Updated: 2020/12/01 04:00:38 by casteria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONCLASSES_HPP
# define EXCEPTIONCLASSES_HPP

# include <exception>
# include <string>
# include <iostream>
# include <errno.h>

class ServerException : public std::exception
{
private:
	std::string		err_message;
public:
	ServerException(const std::string &str)
	{
		err_message += "Error: " + str;
	}
	ServerException(const int &err)
	{
		err_message += "Error: " + std::string(strerror(err));
	}
	virtual const char* what() const throw()
	{
		return (err_message.c_str());
	}
	~ServerException() throw () { return ; }
};

class IrcException : public std::exception
{
private:
	std::string		err_message;
public:
	IrcException(const std::string &str)
	{
		err_message = str;
	}
	virtual const char* what() const throw()
	{
		return (err_message.c_str());
	}
	~IrcException() throw () { return ; }
};

#endif