NAME = lem-in

SOURCES =	main.c \
			error_func.c \
			hashtable.c \
			data_structure_operations.c \
			store_node.c \
			print_map.c \


LIBDIR = libft

SDIR = srcs

ODIR = bin

CFLAGS = -Werror -Wall -Wextra -Ofast -fsanitize=address

INCDIR = includes

LDFLAGS = -L$(LIBDIR) -lft

CC = gcc

SRCS = $(addprefix $(SDIR)/, $(SOURCES:.c=.c))

OBJS = $(addprefix $(ODIR)/, $(SOURCES:.c=.o))

OK = echo "[32m OK ✓ [0m"

all: lib mkbin $(NAME)

lib:
	@make -C $(LIBDIR)

mkbin:
	@mkdir -p $(ODIR)


$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(INCDIR) $(LDFLAGS)
	@echo "\x1B[33;4mCompiled with the rule\x1B[0m   \x1B[33;1m:\x1B[0m " ${CC} $(CFLAGS)
	@$(OK)

$(ODIR)/%.o : $(SDIR)/%.c
	@ echo "[34mAssembling lem-in object : [0m" $@
	@ $(CC) $(CFLAGS) -c -o $@ $< -I$(INCDIR)

clean:
	@ echo "[31mDeleted object directory... [0m"
	@/bin/rm -rf $(ODIR)
	@make -C $(LIBDIR) clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all
