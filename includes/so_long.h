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

#define ESC 53
#define W 13
#define A 0
#define S 1
#define D 2

typedef struct s_img
{
  void *img;
  int w;
  int h;
  int x;
  int y;
  struct s_img *next;
}t_img;

typedef struct s_point
{
  int y;
  int x;
}t_point;

typedef struct s_map
{
  int fd; 
  int w;
  int h;
  char *map;
  char **matrix;
  t_point start;
  int collect;
  int exit;
  int player;
}t_map;

typedef struct s_vars
{
  void *mlx_ptr;
  void *win_ptr;
  t_img *img;
} t_vars;


//parse_map helper functions



void check_map_size(t_map *map);

void parse_matrix(t_map *map);

void check_minimum_asset(t_map *map);

void valid_map(t_map *map);


#endif
