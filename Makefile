NAME = so_long

SRC = main.c 

CC = cc
CC_FLAGS = -Wall -Wextra -Werror

OBJECT_DIR = objects/
OBJECT_SRC = $(addprefix $(OBJECT_DIR), $(SRC:.c=.o))

$(OBJECT_DIR)%.o: %.c includes/so_long.h
	@mkdir -p $(OBJECT_DIR)
	@$(CC) $(CC_FLAGS) -Iincludes -c $< -o $@

#big L is to specify where the compliler should look for libraries. small l is to link the specified library.
#lX11 is the graphical user interface library for X window system, Xext provides extensions for the X window system
$(NAME): $(OBJECT_SRC)
	@$(CC) -o $(NAME) $(OBJECT_SRC) $(CC_FLAGS) mlx/libmlx_Linux.a get_next_line/get_next_line.a ft_printf/libftprintf.a libft/libft.a -lXext -lX11 -lz -lm


all: $(NAME)

clean:
	@rm -rf $(OBJECT_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
