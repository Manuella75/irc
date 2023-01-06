NAME = ircserv
CC = c++
SRCS =	main.cpp\
		server.cpp\
		Command/User.cpp\
		Command/Command.cpp\
		Command/Command_utils.cpp\
		Command/replies.cpp\
		Command/Channel.cpp
OBJS = $(addprefix objs/, $(SRCS:.cpp=.o))
DEPS = $(addprefix objs/, $(SRCS:.cpp=.d))
HEADER = ./includes
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g
RM = rm -rf

all: $(NAME)

objs/%.o: %.cpp
	@echo "Compiling...\t"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -I $(HEADER) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I $(HEADER) -o $(NAME) $(OBJS)

clean:
		rm -rf objs
		$(RM) $(OBJS) $(DEPS)

fclean: clean
		$(RM) $(NAME) $(DEPS)

re: fclean all

-include $(DEPS)

.PHONY: clean fclean re all
