# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: casteria <casteria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 01:48:02 by casteria          #+#    #+#              #
#    Updated: 2020/11/16 17:52:39 by casteria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				ircserv

HEADER_F =			headers
SOURCES_F =			srcs

SOURCES =			main.cpp ServerClass.cpp
SOURCES_REL = 		$(addprefix $(SOURCES_F)/, $(SOURCES))

COMPILER =			clang++
STD_FLAG = 			-std=c++98
FLAGS = 			-Wall -Wextra -Werror $(STD_FLAG)

all: $(NAME)

$(NAME): $(SOURCES_REL)
	$(COMPILER) $(FLAGS) -I $(HEADER_F) $(SOURCES_REL) -o $(NAME)

clean:

fclean: clean

re: fclean all

.PHONY: all clean fclean re
