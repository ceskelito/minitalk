NAME = client server
LIB = libft/libft.a
CLIENT = client
SERVER = server

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

CLISRC = client.c
SERSRC = server.c

CLIOBJS = $(CLISRC:.c=.o)
SEROBJS = $(SERSRC:.c=.o)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
 
all: $(NAME)

client: $(CLIOBJS) $(LIB)
	$(CC) $(CFLAGS) $(CLIOBJS) $(LIB) -o $(CLIENT)

server: $(SEROBJS) $(LIB)
	$(CC) $(CFLAGS) $(SEROBJS) $(LIB) -o $(SERVER)

$(LIB):
	@make -C libft

clean:
	@make -C libft clean
	rm -f $(CLIOBJS) $(SEROBJS)

fclean: clean
	@make -C libft fclean
	$(RM) $(CLIENT) $(SERVER)

re: fclean all

.PHONY: re all clean fclean
