/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:55:27 by kationg           #+#    #+#             */
/*   Updated: 2025/05/09 17:14:06 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf/src/ft_printf.h"
#include "get_next_line/get_next_line.h"
#include "includes/so_long.h"    
#include "libft/libft.h"
#include "mlx/mlx.h"
#include <complex.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static void free_grid(char **grid, t_game *game)
{
  int i = 0;
  while (i < game->map.h)
    free(grid[i++]);
  free(grid);
}

void destroy_sprite(t_game *game)
{
  mlx_destroy_image(game->mlx_ptr, game->player_right.img_ptr);
  mlx_destroy_image(game->mlx_ptr, game->player_left.img_ptr);
  mlx_destroy_image(game->mlx_ptr, game->player_front.img_ptr);
  mlx_destroy_image(game->mlx_ptr, game->player_back.img_ptr);
  mlx_destroy_image(game->mlx_ptr, game->floor.img_ptr);
  mlx_destroy_image(game->mlx_ptr, game->collectibles.img_ptr);
  mlx_destroy_image(game->mlx_ptr, game->wall.img_ptr);
  mlx_destroy_image(game->mlx_ptr, game->exit.img_ptr);
}
void free_map(t_game *game)
{
  if (game->map.matrix)
    free_grid(game->map.matrix, game);
  if (game->map.array)
    free(game->map.array);
}

void error_mssg(char *message, t_game *game)
{
  ft_printf("Error\n""%s\n", message);
  if (game->map.matrix)
    free_grid(game->map.matrix, game);
  if (game->map.array)
    free(game->map.array);
  exit(EXIT_FAILURE);
}

//here im strjoining game->array and a long string and at the same time checking each line is the same width
void check_map_size(t_game *game)
{
  game->map.array = ft_strdup("");
  char *line = get_next_line(game->map.fd);
  int p_width = 0;
  while (line)
  {
    if (game->map.h != 0)
      p_width = game->map.w;
    game->map.w = 0;
    char *temp = game->map.array;
    game->map.array = ft_strjoin(temp, line);
    free(temp);
    while (line[game->map.w] != '\n' && line[game->map.w])
      game->map.w++;
    if (p_width != game->map.w && game->map.h != 0)
    {
      error_mssg("Map is Not Rectangle", game);
      return;
    }
    free(line);
    line = get_next_line(game->map.fd);
    game->map.h++;
  }
}

char **parse_matrix(t_game *game)
{
  int i = 0;
  int len = 0;
  int count = 0;

  char **grid;
  grid = malloc(game->map.h *sizeof(char *));
  while (game->map.array[i])
  {
    len = 0;
    grid[count] = malloc(game->map.w + 1);
    while (game->map.array[i] != '\n' && game->map.array[i])
    {
      i++;
      len++;
    }
    ft_strlcpy(grid[count++], game->map.array + i - len, game->map.w + 1);
    i++;
  }
  return (grid);
}

void check_minimum_asset(t_game *game)
{
  int i = 0;
  while (game->map.array[i])
  {
    
    int c = game->map.array[i];
    if (!ft_strchr("PCE10\n", c))
      error_mssg("Map has unallowed characters", game);
    if (c == PLAYER)
      game->map.player++;
    else if (c == COLLECTIBLES)
      game->map.collect++;
    else if (c == EXIT)
      game->map.exit++;
    i++;
  }
  if (game->map.player != 1 || game->map.collect < 1 || game->map.exit != 1)
    error_mssg("Map does not have the minumum amount of exit/collectible/player", game);
}

void valid_map(t_game *game)
{
  int i = 0;
  int j;
  char **m = game->map.matrix;
  while (i < game->map.h)
  {
    j = 0;
    while (j < game->map.w)
    {
    
      if (m[i][0] != WALL || m[0][j] != WALL || m[game->map.h - 1][j] != WALL || m[i][game->map.w - 1] != WALL)
        error_mssg("Map not surrounded by Walls", game);
      else if (m[i][j] == 'P')
      {
        game->map.starting_p.y = i;
        game->map.starting_p.x = j;
      }
      j++;
    }
    i++;
  }
}

void flood_fill(char **grid, int h, int w, t_point begin)
{
  t_point temp;
  //char c = grid[begin.y][begin.x];
  grid[begin.y][begin.x] = 'F';
  if (grid[begin.y - 1][begin.x] != WALL && grid[begin.y - 1][begin.x] != 'F')
  {
    temp.y = begin.y - 1;
    temp.x = begin.x;
    flood_fill(grid, h, w, temp);
  }
  if (grid[begin.y + 1][begin.x] != WALL && grid[begin.y + 1][begin.x] != 'F')
  {
    temp.y = begin.y + 1;
    temp.x = begin.x;
    flood_fill(grid, h, w, temp);
  }
  if (grid[begin.y][begin.x - 1] != WALL && grid[begin.y][begin.x - 1] != 'F')
  {
    temp.y = begin.y;
    temp.x = begin.x - 1;
    flood_fill(grid, h, w, temp);
  }
  if (grid[begin.y][begin.x + 1] != WALL && grid[begin.y][begin.x + 1] != 'F')
  {
    temp.y = begin.y;
    temp.x = begin.x + 1;
    flood_fill(grid, h, w, temp);
  }
}
static int check_floodfill(char **grid, t_game *game)
{
  int i = 0;
  while (i < game->map.h)
  {
    int j = 0;
    while (j < game->map.w)
    {
      if (ft_strchr("CE", grid[i][j]))
        return (1);
      j++;
    }
    i++;
  }
  return (0);
}

static void check_map(t_game *game)
{
  check_map_size(game);
  game->map.matrix = parse_matrix(game);
  check_minimum_asset(game);
  valid_map(game);
  char **cpy_grid;
  cpy_grid = parse_matrix(game);
  flood_fill(cpy_grid, game->map.h, game->map.w, game->map.starting_p);
  if (check_floodfill(cpy_grid, game))
    error_mssg("Some exit or collectibles cannot be reached", game);
  free_grid(cpy_grid, game);
}

static void check_cml_argument(int argc, char *arg, t_game *game)
{
  if (argc > 2)
    error_mssg("Too many arguments, Usage: ./so_long [map file path]", game);
  else if (argc < 2)
    error_mssg("To run game please include the path of map file", game);
  int i = 0;
  char *file_type;
  file_type = arg;
  while (file_type[i] != '.')
    file_type++;
  if (ft_strncmp(".ber", file_type, 5) != 0)
    error_mssg("invalid map file type, only .ber file is accepted", game);
  int fd = open(arg, O_RDONLY);
  if (fd == -1)
    error_mssg("Unable to open map file", game);
  game->map.fd = fd;
}

void init_mlx(t_game *game)
{
  game->mlx_ptr = mlx_init();
  if (!game->mlx_ptr)
    error_mssg("failed to init mlx ptr", game);
  game->win_ptr = mlx_new_window(game->mlx_ptr, game->map.w * IMG_W, game->map.h * IMG_H, "so_long");
  if (!game->win_ptr)
  {
    free(game->mlx_ptr);    
    error_mssg("failed to make new mlx window", game);
  }
}

t_sprite init_sprite(t_game *game, char *file_path)
{
  t_sprite sprite;

  sprite.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, file_path, &sprite.size.x, &sprite.size.y);
  if (!sprite.img_ptr)
    error_mssg("Sprite was not found", game);
  sprite.img_addr = mlx_get_data_addr(sprite.img_ptr, &sprite.bpp, &sprite.size_line, &sprite.endian);
  return (sprite);
}

void load_sprite(t_game *game)
{
  game->player_front = init_sprite(game, "assets/character/11zon_walk-front.xpm");
  game->player_back = init_sprite(game, "assets/character/11zon_walk-back.xpm");
  game->player_right = init_sprite(game, "assets/character/11zon_walk-right.xpm");
  game->player_left = init_sprite(game, "assets/character/11zon_walk-left.xpm");
  game->collectibles = init_sprite(game, "assets/items/11zon_dynamite.xpm");
  game->exit = init_sprite(game, "assets/items/11zon_door-with-lock.xpm");
  game->floor = init_sprite(game, "assets/terrains/11zon_ground.xpm");
  game->wall = init_sprite(game, "assets/terrains/11zon_wall.xpm");
}

void draw_pixel(t_sprite *buffer,int color, int y, int x)
{
  char *pixel;
  if (color != (int)0xFF000000)
  {
    pixel = buffer->img_addr + ((y * buffer->size_line) + (x *(buffer->bpp / 8)));
    *(unsigned int *)pixel = color;
  }
}

void buffer_img(t_game *game, t_sprite *sprite, t_point pos)
{
  int i;
  int j;
  int color;
  int location;
  i = 0;
  t_point temp;
  while (i < sprite->size.y)
  {
    j = 0;
    while (j < sprite->size.x)
    {
      //bpp is 4 (32/8 == 4, 4bytes per pixel) size_line to skip padding 
      location = (i * sprite->size_line) + (j * sprite->bpp / 8);
      color = *(unsigned int *)(sprite->img_addr + location);
      //img_data + position to move towards the target pixel to avoid byte offset
      temp.y = pos.y + i;
      temp.x = pos.x + j;
      draw_pixel(&game->buffer,color, temp.y, temp.x);
      j++;
    }
    i++; 
  }
}

void render_sprite(t_game *game, char c, t_point pos)
{
  if (c == WALL)
    buffer_img(game, &game->wall, pos);
  else if (c == COLLECTIBLES)
    buffer_img(game, &game->collectibles, pos);
  else if (c == EXIT)
    buffer_img(game, &game->exit, pos);
}

static void buffer_player(t_game *game)
{
  t_point pos;
  pos.y = game->map.starting_p.y * IMG_H;
  pos.x = game->map.starting_p.x * IMG_W;
  if (game->player_state == 0)
    buffer_img(game, &game->player_front, pos);
  else if (game->player_state == 1)
    buffer_img(game, &game->player_back, pos);
  else if (game->player_state == 2)
    buffer_img(game, &game->player_left, pos);
  else if (game->player_state == 3)
    buffer_img(game, &game->player_right, pos);
}

void buffer_fixed_elements(t_game *game)
{
  int i = 0;
  int j;
  t_point pos;
  while (i < game->map.h)
  {
    j = 0;
    while (j < game->map.w)
    {
      pos.y = i * IMG_H;
      pos.x = j * IMG_W;
      buffer_img(game, &game->floor, pos);
      render_sprite(game, game->map.matrix[i][j], pos);
      j++;
    }
    i++;
  }
}

int close_game(t_game* game)
{
  free_map(game);
  destroy_sprite(game);
  if (game->end_state)
    ft_printf("Victory! %i MOVES made \n", game->moves);
  mlx_destroy_window(game->mlx_ptr, game->win_ptr);
  mlx_destroy_display(game->mlx_ptr);
  free(game->mlx_ptr);
  exit(0);
  return (0);
}

int check_boundary(t_game *game, t_point position)
{
  int y = position.y;
  int x = position.x;
  if (game->map.matrix[y][x] == WALL)
    return 0;
  else if (game->map.matrix[y][x] == COLLECTIBLES)
  {
    game->map.collect -= 1;
    game->map.matrix[y][x] = FLOOR;
    if (game->map.collect == 0)
      game->end_state = 1;
  }
  else if (game->map.matrix[y][x] == EXIT && game->end_state)
  {
    game->moves++;
    close_game(game);
  }
  return 1;
}

int handle_input(int keycode, t_game *game)
{
  t_point temp = game->map.starting_p;
  
  if (keycode == XK_Escape)
    close_game(game);
  else if (keycode == XK_w)
  {
    temp.y -= 1;
    if (check_boundary(game, temp))
    {
      game->map.starting_p.y -= 1;
      game->moves++;
      game->player_state = 1;
    }
  } 
  else if (keycode == XK_s)
  {
    temp.y += 1;
    if (check_boundary(game, temp))
    {
      game->map.starting_p.y += 1;
      game->moves++;
      game->player_state = 0;
    }
  }

  else if (keycode == XK_a)
  {
    temp.x -= 1;
    if (check_boundary(game, temp))
    {
      game->map.starting_p.x -= 1;
      game->moves++;
      game->player_state = 2;
    }
  }
  else if (keycode == XK_d)
  {
    temp.x += 1;
    if (check_boundary(game, temp))
    {
      game->map.starting_p.x += 1;
      game->moves++;
      game->player_state = 3;
    }
  }
  return (0);
}

//must return int cuz loop hook expects an int to be returned to indicate success
int print_game_map(t_game *game)
{
  game->buffer.img_ptr = mlx_new_image(game->mlx_ptr, game->map.w * 32, game->map.h * 32);
  game->buffer.img_addr = mlx_get_data_addr(game->buffer.img_ptr, &game->buffer.bpp, &game->buffer.size_line, &game->buffer.endian);
  buffer_fixed_elements(game);
  buffer_player(game);
  mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->buffer.img_ptr, 0, 0);
  char *movements = ft_itoa(game->moves);
  char *string = ft_strjoin("Movements: ", movements);
  mlx_string_put(game->mlx_ptr, game->win_ptr, 40, 20, 255, string);
  free(string);
  free(movements);
  mlx_destroy_image(game->mlx_ptr, game->buffer.img_ptr);
  return (0);
}

int main(int argc, char *argv[])
{
  t_game game;
  ft_memset(&game, 0, sizeof(t_game));
  check_cml_argument(argc, argv[1], &game);
  check_map(&game);
  init_mlx(&game);
  load_sprite(&game);
  mlx_loop_hook(game.mlx_ptr, print_game_map, &game);
  mlx_hook(game.win_ptr, 17, 0L, close_game,  &game);
  mlx_key_hook(game.win_ptr, handle_input, &game);
  mlx_loop(game.mlx_ptr);
}
