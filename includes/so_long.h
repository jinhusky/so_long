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
#include <X11/keysym.h>

#define IMG_H 64
#define IMG_W 64

#define FLOOR '0'
#define WALL '1'
#define COLLECTIBLES 'C'
#define EXIT 'E'
#define PLAYER 'P'

typedef struct s_point
{
  int y;
  int x;
}t_point;

typedef struct s_sprite
{
  void *img_ptr;
  t_point size;
  int bpp;
  int size_line;
  int endian;
  char *img_addr;
  struct s_sprite *next;
}t_sprite;

typedef struct s_map
{
  t_point starting_p;
  int fd;
  //t_point size;
  int w;
  int h;
  char *array;
  char **matrix;
  int collect;
  int exit;
  int player;
}t_map;

typedef struct s_game
{
  void *mlx_ptr;
  void *win_ptr;
  t_map map;
  t_sprite buffer;
  t_sprite floor;
  t_sprite wall;
  t_sprite collectibles;
  t_sprite exit;
  t_sprite player_front;
  t_sprite player_back;
  t_sprite player_right;
  t_sprite player_left;
  int player_state;
  int end_state;
  int moves;
} t_game;

//parse_map helper functions



void check_map_size(t_game *map);

char **parse_matrix(t_game *map);

void check_minimum_asset(t_game *map);

void valid_map(t_game *map);


#endif
