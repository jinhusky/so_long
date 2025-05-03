/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:55:27 by kationg           #+#    #+#             */
/*   Updated: 2025/05/03 15:45:53 by kationg          ###   ########.fr       */
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

void error_mssg(char *message, t_game *game)
{
  ft_printf("Error\n""%s\n", message);
  free(game->mlx_ptr);
  exit(EXIT_FAILURE);
}

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
    game->map.array = ft_strjoin(game->map.array, line);
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
  if (game->map.player != 1 || game->map.collect < 1 || game->map.exit < 1)
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
}

static void check_cml_argument(int argc, char *arg, t_game *game)
{
  if (argc > 2)
    error_mssg("Too many arguments, Usage: ./so_long [map file path]", game);
  else if (argc < 2)
    error_mssg("To run game please include the path of map file", game);
  int fd = open(arg, O_RDONLY);
  if (fd == -1)
    error_mssg("Unable to open map file", game);
  game->map.fd = fd;
}

void init_mlx(t_game *game)
{
  game->mlx_ptr = mlx_init();
  if (!game->mlx_ptr)
    error_mssg("failed to init mlx ptr" , game);
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

  sprite.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, file_path, &sprite.x, &sprite.y);
  if (!sprite.img_ptr)
    error_mssg("Sprite was not found", game);
  return (sprite);
}



void load_sprite(t_game *game)
{
  
  game->player = init_sprite(game, "assets/character/11zon_walk-front.xpm");
  game->collectibles = init_sprite(game, "assets/items/11zon_dynamite.xpm");
  game->exit = init_sprite(game, "assets/items/11zon_door-with-lock.xpm");
  game->floor = init_sprite(game, "assets/terrains/11zon_ground.xpm");
  game->wall = init_sprite(game, "assets/terrains/11zon_wall.xpm");
}

void render_sprite(t_game *game, char c, int y, int x)
{
  mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->floor.img_ptr, IMG_W * x, IMG_H * y);
  if (c == WALL)
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->wall.img_ptr, IMG_W * x, IMG_H * y);
  else if (c == COLLECTIBLES)
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->collectibles.img_ptr, IMG_W * x, IMG_H * y);
  else if (c == EXIT)
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->exit.img_ptr, IMG_W * x, IMG_H * y);
}

static void player_position(t_game *game)
{
  mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->player.img_ptr, IMG_W * game->map.starting_p.x, game->map.starting_p.y * IMG_H);
}


int render_map(t_game *game)
{
  int i = 0;
  int j;
  while (i < game->map.h)
  {
    j = 0;
    while (j < game->map.w)
    {
      render_sprite(game, game->map.matrix[i][j], i, j);
      j++;
    }
    i++;
  }
  player_position(game);
  return (0);
}


int close_game(t_game* game)
{
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
  
  if (keycode == 65307)
    close_game(game);
  else if (keycode == 119)
  {
    temp.y -= 1;
    if (check_boundary(game, temp))
    {
      game->map.starting_p.y -= 1;
      game->moves++;
    }
  } 
  else if (keycode == 115)
  {
    temp.y += 1;
    if (check_boundary(game, temp))
    {
      game->map.starting_p.y += 1;
      game->moves++;
    }
  }
  else if (keycode == 97)
  {
    temp.x -= 1;
    if (check_boundary(game, temp))
    {
      game->map.starting_p.x -= 1;
      game->moves++;
    }
  }
  else if (keycode == 100)
  {
    temp.x += 1;
    if (check_boundary(game, temp))
    {
      game->map.starting_p.x += 1;
      game->moves++;
    }
  }
  render_map(game);
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
  render_map(&game);
  mlx_hook(game.win_ptr, 17, 0L, close_game,  &game);
  mlx_key_hook(game.win_ptr, handle_input, &game);
  mlx_loop(game.mlx_ptr);
}


  /*
  t_data data;
  data.mlx_ptr = mlx_init();
  if (!data.mlx_ptr)
    return (1);
  data.win_ptr = mlx_new_window(data.mlx_ptr, 1200, 800, "hi :_)");
  if (!data.win_ptr)
    return (free(data.mlx_ptr), 1);


  int x;
  int y;
  void *tile = mlx_xpm_file_to_image(data.mlx_ptr, "textures/0_Template_Background1.xpm ", &x, &y);
  mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, tile, 0 , 0);
  mlx_loop(data.mlx_ptr);

 
  t_data *data;
  data = malloc(sizeof(t_data));
  data -> mlx_ptr = mlx_init();
  if (!data -> mlx_ptr)
    return (1);
  data -> win_ptr = mlx_new_window(data -> mlx_ptr, 1920, 1080, "hi :_)");
  if (!data -> win_ptr)
    return (free(data -> mlx_ptr), 1);
  int x ;
  int y ;
  mlx_hook(data -> win_ptr, 2, 0, quit, data);
  void *tile = mlx_xpm_file_to_image(data -> mlx_ptr, "textures/0_Template_Tileset_Background1.xpm", &x, &y);
  mlx_put_image_to_window(data -> mlx_ptr, data -> win_ptr, tile, 0 , 0);
  mlx_loop(data -> mlx_ptr); 
}
*/


