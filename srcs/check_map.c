/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:18:06 by kationg           #+#    #+#             */
/*   Updated: 2025/06/04 18:13:07 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

//here im strjoining game->array and a long string and at the same time checking each line is the same width
static void check_map_size(t_game *game)
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

static char **parse_matrix(t_game *game)
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
    ft_strlcpy(grid[count], game->map.array + i - len, game->map.w + 1);
    count++;
    if (game->map.array[i] == '\n')
      i++;
  }
  return (grid);
}


static void check_minimum_asset(t_game *game)
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

static void valid_map(t_game *game)
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


void check_map(t_game *game)
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

