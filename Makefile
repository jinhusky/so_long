# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kationg <kationg@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/09 15:09:41 by kationg           #+#    #+#              #
#    Updated: 2025/03/11 14:52:54 by kaijing          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
SRCS = parse_map.c 
minilibx = mlx/libmlx.a
CC_FLAGS = -Wall -Werror -Wextra
OBJECT_DIR = object/
OBJECT_PREFIXED = $(addprefix $(OBJECT_DIR), $(OBJECT))

OBJECT = $(SRC:.c=.o)

MLX_FlAGS = -I -L /usr/X11/lib -Lincludes -L./mlx -lmlx -Imlx -lXext -lX11 -lz -lm libft/libft.a ft_printf/libftprintf.a 

$(OBJECT_DIR)%.o : %.c includes/so_long.h 
	@mkdir -p $(OBJECT_DIR)
	@mkdir -p $(OBJECT_DIR)srcs
	@mkidr -p $(OBJECT_DIR)srcs/generate
	@mkdir -p $(OBJECT_DIR)srcs/displaying
	@mkdir -p $(OBJECT_DIR)srcs/handling
	@cc $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJECT_PREFIXED) maker
	@gcc -o $(NAME) $(OBJECT_PREFIXED) $(CC_FLAGS) $(MLX_FlAGS)

all: $(NAME)
	
bonus: $(NAME_BONUS)

maker:
	@make -C mlx
	@make bonus -C libft
	@make -C ft_printf

clean:
	@rm -rf $(OBJECT_DIR)
	@make clean -C libft
	@make clean -C ft_printf

fclean:
	@make clean -C mlx
	@make fclean -C libft
	@make fclean -C ft_printf
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
