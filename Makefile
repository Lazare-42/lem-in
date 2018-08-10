NAME = lem-in

SOURCES =	main.c \

LIBDIR = libft

SDIR = srcs

ODIR = bin

CFLAGS = -Werror -Wall -Wextra -Ofast -O3

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
	@ echo "[35mEntering lem-in Makefile...[0m"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(INCDIR) $(LDFLAGS)
	@$(OK)

$(ODIR)/%.o : $(SDIR)/%.c
	@ echo "[34mAssembling lem-in object: [0m" $@
	@ $(CC) $(CFLAGS) -c -o $@ $< -I$(INCDIR)

clean:
	@ echo "[31mDeleted object directory... [0m"
	@/bin/rm -rf $(ODIR)
	@make -C $(LIBDIR) clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all
