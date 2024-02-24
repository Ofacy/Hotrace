NAME = hotrace

SRCS_DIR = ./
SRCS = main.c \
	   get_next_line.c \
	   ft_memcpy.c \
	   ft_strn2join_free_s1.c \
	   hash.c \
	   hashmap.c \
	   vector_init.c \
	   clear_vector.c \
	   add_vector.c \
	   ft_strcmp.c \

CFLAGS = -g3 -Wall -Wextra -Werror -MMD -MP

OUTDIR = obj
OBJECTS = ${SRCS:%.c=$(OUTDIR)/%.o}

DEPS_FILES = ${OBJECTS:.o=.d}


all: $(NAME)

norm:
	norminette

-include $(DEPS_FILES)

${NAME}: $(OBJECTS)
	cc $(CFLAGS) -o $(NAME) $(OBJECTS)

$(OUTDIR)/%.o: $(SRCS_DIR)/%.c | $(OUTDIR)
	cc $(CFLAGS) -o $@ -c $<

$(OUTDIR):
	mkdir -p $(OUTDIR)
clean:
	rm -f $(OBJECTS) $(DEPS_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all norm
