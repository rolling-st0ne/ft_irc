# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwynton <gwynton@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 01:48:02 by casteria          #+#    #+#              #
#    Updated: 2020/11/24 21:10:45 by gwynton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				ircserv

HEADER_F =			headers
SOURCES_F =			srcs

HEADERS = 			ExceptionsClasses.hpp irc.hpp ServerClass.hpp IrcApiClass.hpp \
					UserClass.hpp utils.hpp
SOURCES =			main.cpp ServerClass.cpp init.cpp create_server.cpp \
					ClientClass.cpp UserClass.cpp IrcApiClass.cpp \
					utils.cpp
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
