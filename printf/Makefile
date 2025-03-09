NAME = libftprintf.a
LIBFT_PATH = includes/libft/
CC_FLAGS = -Wall -Wextra -Werror -I./includes/

SOURCE = src/ft_printf.c src/ft_putnbr.c src/ft_putstr.c src/ft_putptr.c
OBJECTS = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT_PATH)libft.a
	@mkdir -p libft_obj                 
	@cd libft_obj && ar -x ../$(LIBFT_PATH)libft.a  
	ar rc $(NAME) $(OBJECTS) libft_obj/*.o 

$(LIBFT_PATH)libft.a:
	make -C $(LIBFT_PATH)

%.o: %.c
	cc $(CC_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -rf libft_obj
	make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re

