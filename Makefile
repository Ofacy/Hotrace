NAME = philo

SRCS_DIR = ./
SRCS = main.c

CFLAGS = -g3 -Wall -Wextra -Werror -MMD -MP

OUTDIR = obj
OBJECTS = ${SRCS:%.c=$(OUTDIR)/%.o}

DEPS_FILES = ${OBJECTS:.o=.d}


all: lib $(NAME)

norm:
	norminette

-include $(DEPS_FILES)

${NAME}: $(OBJECTS)
	cc $(CFLAGS) -lpthread -o $(NAME) $(OBJECTS)

$(OUTDIR)/%.o: $(SRCS_DIR)/%.c | $(OUTDIR)
	cc $(CFLAGS) -o $@ -c $<

$(OUTDIR):
	mkdir -p $(OUTDIR)
clean:
	rm -f $(OBJECTS) $(DEPS_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: lib clean fclean re all norm
