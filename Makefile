NAME = so_long

SRC = main.c parse_map.c

CC = cc
CC_FLAGS = -Wall -Wextra -Werror

OBJECT_DIR = objects/
OBJECT_SRC = $(addprefix $(OBJECT_DIR), $(SRC:.c=.o))

$(OBJECT_DIR)%.o: %.c includes/so_long.h
	@mkdir -p $(OBJECT_DIR)
	@$(CC) $(CC_FLAGS) -Iincludes -c $< -o $@


$(NAME): $(OBJECT_SRC)
	@$(CC) -o $(NAME) $(OBJECT_SRC) $(CC_FLAGS) mlx/libmlx_Linux.a get_next_line/get_next_line.a ft_printf/libftprintf.a libft/libft.a -lXext -lX11 -lz -lm


all: $(NAME)

clean:
	@rm -rf $(OBJECT_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
