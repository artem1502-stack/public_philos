CC			:= gcc
FLAG		:= -Wall -Wextra -Werror

SRCNAMES	:= main.c utils.c parsing.c cleanup.c start_treads.c

CNAMES		:=	$(SRCNAMES)
ONAMES		:=	$(SRCNAMES:.c=.o)

HNAMES		:= philo.h messages.h
NAME		:= philo
rm			:= rm -f

all: $(NAME)

$(NAME): $(ONAMES) $(HNAMES) Makefile
	@$(CC) $(ONAMES) -o $(NAME)
	@printf "Makefile: philosophers successfuly built\n"

%.o: %.c $(HNAMES) Makefile
	@$(CC) $(FLAG) -c $< -o $@

clean:
	@$(RM) $(ONAMES)
	@printf "Makefile: all non-source files deleted\n"

fclean: clean
	@$(RM) $(NAME) $(BNAME)
	@printf "Even the 'philo'\n"

re: fclean all

.PHONY: all clean fclean re
