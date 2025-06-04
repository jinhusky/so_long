/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:14:25 by kationg           #+#    #+#             */
/*   Updated: 2025/06/04 18:13:35 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

int check_floodfill(char **grid, t_game *game)
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
