CC			:= gcc
FLAG		:= -Wall -Wextra -Werror

SRCNAMES	:= main_bonus.c utils_bonus.c parsing_bonus.c cleanup_bonus.c start_process_bonus.c sems_bonus.c

CNAMES		:=	$(SRCNAMES)
ONAMES		:=	$(SRCNAMES:.c=.o)

HNAMES		:= philo_bonus.h messages_bonus.h
NAME		:= philo_bonus
rm			:= rm -f

all: $(NAME)

$(NAME): $(ONAMES) $(HNAMES) Makefile
	@$(CC) $(ONAMES) -o $(NAME)
	@printf "Makefile: $(NAME) successfuly built\n"

%.o: %.c $(HNAMES) Makefile
	@$(CC) $(FLAG) -c $< -o $@

clean:
	@$(RM) $(ONAMES)
	@printf "Makefile: all non-source files deleted\n"

fclean: clean
	@$(RM) $(NAME) $(BNAME)
	@printf "Even the '$(NAME)'\n"

re: fclean all

.PHONY: all clean fclean re
