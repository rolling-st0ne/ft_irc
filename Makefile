# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 01:48:02 by casteria          #+#    #+#              #
#    Updated: 2020/11/22 01:19:22 by casteria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				ircserv

HEADER_F =			headers
SOURCES_F =			srcs

HEADERS = 			ExceptionsClasses.hpp irc.hpp ServerClass.hpp
SOURCES =			main.cpp ServerClass.cpp init.cpp create_server.cpp \
					ClientClass.cpp UserClass.cpp
SOURCES_REL = 		$(addprefix $(SOURCES_F)/, $(SOURCES))
HEADERS_REL = 		$(addprefix $(HEADER_F)/, $(HEADERS))
OBJECTS_REL =		$(SOURCES_REL:.cpp=.o)

COMPILER =			clang++
STD_FLAG = 			-std=c++98
FLAGS = 			-Wall -Wextra -Werror $(STD_FLAG) -I $(HEADER_F)

all: $(NAME)

$(NAME): $(OBJECTS_REL)
	$(COMPILER) $(FLAGS) $(OBJECTS_REL) -o $(NAME)

%.o: %.cpp $(HEADERS_REL)
	$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS_REL)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
