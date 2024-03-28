CFLAGS = #-Wall -Wextra -Werror

SRCC = client.c

SRCS = server.c

OBJC = $(SRCC:.c=.o)

OBJS = $(SRCS:.c=.o)

CLIENT = client

SERVER = server

all: $(CLIENT) $(SERVER)

$(CLIENT): $(OBJC)
	cc $(CFLAGS) $(OBJC) -o $@

$(SERVER): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(OBJS) $(OBJC)

fclean: clean
	rm -f $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re
