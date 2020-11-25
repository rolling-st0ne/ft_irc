# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: casteria <casteria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 01:48:02 by casteria          #+#    #+#              #
#    Updated: 2020/11/25 20:25:55 by casteria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				ircserv

HEADER_F =			headers
SOURCES_F =			srcs

HEADERS = 			ExceptionsClasses.hpp irc.hpp ServerClass.hpp IrcApiClass.hpp \
					UserClass.hpp utils.hpp

COMMANDS_F = 		commands
COMMANDS_SRCS = 	nick.cpp
COMMANDS_SRCS_REL =	$(addprefix $(COMMANDS_F)/, $(COMMANDS_SRCS))

MAIN_SOURCES = 		main.cpp ServerClass.cpp init.cpp ClientClass.cpp \
					UserClass.cpp IrcApiClass.cpp utils.cpp

ALL_SOURCES =		$(MAIN_SOURCES) $(COMMANDS_SRCS_REL)
ALL_SOURCES_REL = 	$(addprefix $(SOURCES_F)/, $(ALL_SOURCES))
HEADERS_REL = 		$(addprefix $(HEADER_F)/, $(HEADERS))
OBJECTS_REL =		$(ALL_SOURCES_REL:.cpp=.o)

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
