# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kationg <kationg@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/09 15:09:41 by kationg           #+#    #+#              #
#    Updated: 2025/03/18 11:21:10 by kaijing          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
SRCS = main.c parse_map.c 
CC_FLAGS = -Wall -Werror -Wextra
OBJECT_DIR = object/
OBJECT_PREFIXED = $(addprefix $(OBJECT_DIR), $(SRC:.c=.o))

MLX_FlAGS = mlx/libmlx_Linux.a get_next_line/get_next_line.a ft_printf/libftprintf.a libft/libft.a -lXext -lX11 -lz -lm

$(OBJECT_DIR)%.o : %.c includes/so_long.h 
	@mkdir -p $(OBJECT_DIR)
	@cc $(CC_FLAGS) -Iincludes -c $< -o $@

$(NAME): $(OBJECT_PREFIXED) 
	@cc -o $(NAME) $(OBJECT_PREFIXED) $(CC_FLAGS) $(MLX_FlAGS)

all: $(NAME)
	
bonus: $(NAME_BONUS)

clean:
	@rm -rf $(OBJECT_DIR)

fclean:
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
