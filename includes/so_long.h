#ifndef SO_LONG_H
# define SO_LONG_H

#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <fcntl.h>
#include <errno.h>
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

//check_map
void check_map(t_game *game);
int check_floodfill(char **grid, t_game *game);
void flood_fill(char **grid, int h, int w, t_point begin);

//free mem and error handling
void destroy_sprite(t_game *game);
void free_map(t_game *game);
void error_mssg(char *message, t_game *game);
void free_grid(char **grid, t_game *game);

//mlx functions
void init_mlx(t_game *game);
int close_game(t_game* game);
void load_sprite(t_game *game);

//rendering map
int print_game_map(t_game *game);
void buffer_sprite(t_game *game, t_sprite *sprite, t_point pos);

//game mechanics 
int handle_input(int keycode, t_game *game);








#endif
