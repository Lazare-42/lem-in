NAME = lem-in

SOURCES =	main.c \
			error_func.c \
			hashtable.c \
			data_structure_operations.c \
			store_node.c \
			parsing.c \
			swap_end_begin_rooms.c \
			lemin_plst.c \
			lemin_ilst.c \
			get_paths.c \
			path_operations.c \
			path_operations_2.c \
			ft_mat.c \
			dijkstra.c \
			lemin_mat.c \
			lemin_heap.c \
			heap_add_del.c \
			output_print.c \

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

all: lib mkbin $(NAME) ./includes/lemin.h ./Makefile

lib:
	@make -C $(LIBDIR)

mkbin:
	@mkdir -p $(ODIR)


$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(INCDIR) $(LDFLAGS)
	@echo "\x1B[33;4mCompiled with the rule\x1B[0m   \x1B[33;1m:\x1B[0m " ${CC} $(CFLAGS)
	@$(OK)

$(ODIR)/%.o : $(SDIR)/%.c ./Makefile ./includes/lemin.h ./libft/libft.a
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
