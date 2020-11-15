# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: casteria <mskoromec@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 01:48:02 by casteria          #+#    #+#              #
#    Updated: 2020/11/16 02:09:01 by casteria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				ircserv

HEADER_F =			headers
SOURCES_F =			srcs

SOURCES =			main.cpp ServerClass.cpp
SOURCES_REL = 		$(addprefix $(SOURCES_F)/, $(SOURCES))

COMPILER =			clang++
FLAGS = 			-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SOURCES_REL)
	$(COMPILER) $(FLAGS) -I $(HEADER_F) $(SOURCES_REL) -o $(NAME)

clean:

fclean: clean

re: fclean all

.PHONY: all clean fclean re
