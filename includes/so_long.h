#ifndef SO_LONG_H
# define SO_LONG_H

#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include "../ft_printf/src/ft_printf.h"
#include "../get_next_line/get_next_line.h"
#include <stdlib.h>


//parse_map helper functions
void check_map_size(int fd, int *width, int *height);
char **parsing(int width, int height, int fd);

#endif 
