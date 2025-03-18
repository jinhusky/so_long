/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:27:42 by kationg           #+#    #+#             */
/*   Updated: 2025/03/18 11:30:07 by kaijing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"


typedef struct s_point
{
  int x;
  int y;
} t_point;



//the function takes char * data type for file path because the file path is passed as a string
//added to check that it has same width in all rows, to ensure map is rectangled shaped
void check_map_size(int fd, int *width, int *height)
{
  char *line = get_next_line(fd);
  int p_width = 0;
  while (line)
  {
    if (height != 0)
      p_width = *width;
    *width = 0;
    while (line[*width] != '\n' && line[*width] )
    {
      (*width)++;
    }
    if (p_width != *width)
    {
      ft_printf("Error \n MAP IS NOT RECTANGLE\n");
      return ;
    }
    free(line);
    line = get_next_line(fd);
    (*height)++;
  }
}

//malloc once here (total malloc = 1)
char **parsing(int width, int height, int fd)
{
  int i = 0;
  char **res = malloc(height * sizeof(char *));
  char *line = get_next_line(fd);
  while (line)
  {
    res[i++] = ft_strdup(line);
    free(line);
    line = get_next_line(fd);
  }
  width ++;
  return (res);
}

//find out find there is only Player, count Exit, count collectibles, also check if map is surrounded by walls
/*
int valid_map(char **map)
{
  int i = 0;
  int j = 0;
  int player = 0;
  int collectibles = 0;
  int exits = 0;

  while (i < height)
  {
    j = 0;
    while (j < width)
    {
      if (map[i][0] != '1' || map[0][j] != '1')
      {
        ft_printf("Map is not surrounded by walls");
        return (1);
      }
      else if (map[i][j] == 'P')
      {
        t_point.y = i;
        t_point.x = y;
        player++;
      }
      else if (map[i][j] == 'C')
        collectibles++;
      else if (map[i][j] == 'E')
        exits++;
      j++;
    }
    i++;
  }

  if (exits < 1 || collectibles < 1 || player != 1)
  {
    ft_printf("Map does not have the minimum amount of exit/collectibles/player");
    return (1);
  }
}                  

//use flood_fill algorithm to check if all collectibles and exits are accessible, starting from player position
static check valid_path(char **map, t_point size, t_point begin)
{
  t_point c = map[begin.y][begin.x];
  map[begin.y][begin.x] = '1';
  t_point newpoint;
  if (begin.y > 0 && map[begin.y - 1][begin.x])
  {
    newpoint.y = begin.y - 1;
    newpoint.x = begin.x;
    valid_path(map, size, newpoint);
  }
  if (begin.x < size.x - 1  )

}       */           
