# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: casteria <casteria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 01:48:02 by casteria          #+#    #+#              #
#    Updated: 2020/11/17 10:35:36 by casteria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				ircserv

HEADER_F =			headers
SOURCES_F =			srcs

HEADERS = 			ExceptionsClasses.hpp irc.hpp ServerClass.hpp
SOURCES =			main.cpp ServerClass.cpp init.cpp create_server.cpp
SOURCES_REL = 		$(addprefix $(SOURCES_F)/, $(SOURCES))
HEADERS_REL = 		$(addprefix $(HEADER_F)/, $(HEADERS))

COMPILER =			clang++
STD_FLAG = 			-std=c++98
FLAGS = 			-Wall -Wextra -Werror $(STD_FLAG)

all: $(NAME)

$(NAME): $(SOURCES_REL) $(HEADERS_REL)
	$(COMPILER) $(FLAGS) -I $(HEADER_F) $(SOURCES_REL) -o $(NAME)

clean:

fclean: clean

re: fclean all

.PHONY: all clean fclean re
