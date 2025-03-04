NAME	= $(CLIENT) $(SERVER)
LIB 	:= LIBFT/libft.a

CC 		:= cc
CFLAGS 	:= -Wall -Wextra -Werror
RM 		:= rm -f

MODE	?= mandatory

ifeq ($(MODE), bonus)
CLIENT		:= client_bonus
SERVER		:= server_bonus
DIR             := bonus
CLIENT_SRC      := bonus_client.c
SERVER_SRC      := bonus_server.c
else
CLIENT		:= client
SERVER		:= server
DIR             := mandatory
CLIENT_SRC      := client.c
SERVER_SRC      := server.c
endif

CLIENT_OBJ = $(DIR)/$(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(DIR)/$(SERVER_SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
 
all: $(NAME)

$(CLIENT): $(CLIENT_OBJ) $(LIB)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LIB) -o $(CLIENT)

$(SERVER): $(SERVER_OBJ) $(LIB)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(LIB) -o $(SERVER)

bonus:
	$(MAKE) MODE=bonus $(filter-out bonus, $(MAKECMDGOALS))
	@exit
	
$(LIB):
	@make -C LIBFT

clean:
	@make -C LIBFT clean
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ)

fclean: clean
	@make -C LIBFT fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: re all clean fclean bonus
