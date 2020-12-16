# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 01:48:02 by casteria          #+#    #+#              #
#    Updated: 2020/12/16 20:26:43 by casteria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				ircserv

HEADER_F =			headers
SOURCES_F =			srcs

HEADERS = 			ExceptionsClasses.hpp irc.hpp ServerClass.hpp IrcApiClass.hpp \
					UserClass.hpp utils.hpp ChannelClass.hpp HostClass.hpp

COMMANDS_F = 		commands
COMMANDS_SRCS = 	nick.cpp pass.cpp user.cpp server.cpp join.cpp privmsg.cpp \
					part.cpp topic.cpp quit.cpp notice.cpp mode.cpp kick.cpp \
					njoin.cpp
COMMANDS_SRCS_REL =	$(addprefix $(COMMANDS_F)/, $(COMMANDS_SRCS))

MAIN_SOURCES = 		main.cpp ServerClass.cpp ClientClass.cpp \
					UserClass.cpp IrcApiClass.cpp utils.cpp \
					ChannelClass.cpp HostClass.cpp

ALL_SOURCES =		$(MAIN_SOURCES) $(COMMANDS_SRCS_REL)
ALL_SOURCES_REL = 	$(addprefix $(SOURCES_F)/, $(ALL_SOURCES))
HEADERS_REL = 		$(addprefix $(HEADER_F)/, $(HEADERS))
OBJECTS_REL =		$(ALL_SOURCES_REL:.cpp=.o)

COMPILER =			clang++
STD_FLAG = 			-std=c++98
SSL_LIB = 			-L/usr/lib -lssl -lcrypto
FLAGS = 			-Wall -Wextra -Werror $(STD_FLAG) -I $(HEADER_F) -D DEBUG_MODE=1

all: $(NAME)

$(NAME): $(OBJECTS_REL)
	$(COMPILER) $(FLAGS) $(SSL_LIB) $(OBJECTS_REL) -o $(NAME)

%.o: %.cpp $(HEADERS_REL)
	$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS_REL)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
