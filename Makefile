# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mettien <mettien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 16:53:48 by mettien           #+#    #+#              #
#    Updated: 2022/11/18 20:17:07 by mettien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CC = c++
SRCS = main.cpp server.cpp Command/User.cpp Command/Command.cpp
OBJS = ${SRCS:.cpp=.o}
DEPS = ${SRCS:.cpp=.d}
HEADER = ./includes
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g
RM = rm -rf

all: ${NAME}

%.o         : %.cpp
	@echo "Compiling...\t" 
	@$(CC) $(CFLAGS) -MMD -MP -I $(HEADER) -o $@ -c $<

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I $(HEADER) -o $(NAME) $(OBJS)

clean:
		@${RM} ${OBJS} ${DEPS}

fclean: clean
		@${RM} ${NAME} ${DEPS}

re: fclean all

-include $(DEPS)

.PHONY: clean fclean re all
