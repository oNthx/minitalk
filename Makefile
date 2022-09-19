SERVER	= server.c
CLIENT	= client.c

SERVNAME	= server
CLIENTNAME	= client
CFLGS		= -Wall -Werror -Wextra
CC			= gcc
RM			= rm -f
NAME		= $(SERVNAME) $(CLIENTNAME)

all: $(NAME)

$(SERVNAME): $(SERVER)
	$(CC) $(CFLGS) $(SERVER) -o $(SERVNAME)

$(CLIENTNAME): $(CLIENT)
	$(CC) $(CFLGS) $(CLIENT) -o $(CLIENTNAME)

clean:
	$(RM) $(SERVNAME) $(CLIENTNAME)

re: fclean all

fclean: $(clean)
	@$(RM) $(NAME)

.PHONY: all clean fclean re
