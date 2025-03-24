#ifndef SO_LONG_H
# define SO_LONG_H

#include "../libft/libft.h"
#include "../ft_printf/src/ft_printf.h"
#include "../get_next_line/get_next_line.h"
#include "../mlx/mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
typedef struct s_data
{
  void *mlx_ptr;
  void *win_ptr;
} t_data;

typedef struct s_point
{
  int y;
  int x;
}t_point;

//parse_map helper functions
char *check_map_size(int fd, int *width, int *height);

 char **parsing(int width, int height, char * fd);

int check_minimum_asset(char *map);

int valid_map(char **map, int width, int height, t_point *begin);


#endif
