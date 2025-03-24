/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:27:42 by kationg           #+#    #+#             */
/*   Updated: 2025/03/22 01:16:56 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf/src/ft_printf.h"
#include "includes/so_long.h"
#include <unistd.h>

//the function takes char * data type for file path because the file path is passed as a string
//added to check that it has same width in all rows, to ensure map is rectangled shaped (checks for rectangle before malloc)
char *check_map_size(int fd, int *width, int *height)
{
  char *buffer;
  buffer = ft_strdup("");
  char *line = get_next_line(fd);
  int p_width = 0;
  while (line)
  {
    if (height != 0)
      p_width = *width;
    *width = 0;
    buffer = ft_strjoin(buffer, line); 
    while (line[*width] != '\n' && line[*width] )
    {
      (*width)++;
    }
    if (p_width != *width && *height != 0)
    {
      perror("Map is not rectangle\n");
      return (NULL);
    }
    free(line);
    line = get_next_line(fd);
    (*height)++;
  }
  return (buffer);
}


//malloc once here (total malloc = 1)
//once map is stored, now we need to make into 2D array so that it can flood_fill
char **parsing(int width, int height, char *buffer)
{
  int i = 0;
  int len = 0;
  int count = 0;
  char **res = malloc(height * sizeof(char *));
  
  while (buffer[i])
  {
    len = 0;
    //since we are using strlcpy we need an extra byte for \0 since strlcpy
    res[count] = malloc(width + 1);
    while (buffer[i] != '\n' && buffer[i])
    {
      i++;
      len++;
    }
    // +1 size because strlcpy will only copy up till size -1 to ensure null termination
    ft_strlcpy(res[count++], buffer + i - len, width + 1);

    i++;
  }
  return (res);
}

int check_minimum_asset(char *map)
{
  int i = 0;
  int collectibles = 0;
  int players = 0;
  int exits = 0;
  while (map[i])
  {
    if (map[i] == 'P')
      players++;
    else if (map[i] == 'C')
      collectibles++;
    else if (map[i] == 'E')
      exits++;
    i++;
  }
  if (players != 1)
    ft_printf("Error\none player per game");
  else if (collectibles < 1)
    ft_printf("Error\nneed at least one collectible");
  else if (exits < 1)
    ft_printf("Error\nneed at least one collectible");
  else 
    return (1);
  return (0);
}

int valid_map(char **map, int width, int height, t_point *begin)
{
  int i = 0;
  int j = 0;
  while (i < height)
  {
    j = 0;
    while (j < width)
    {
      if (map[i][0] != '1' || map[0][j] != '1' || map[height -1][j] != '1' || map[i][width - 1] != '1')
      {
        ft_printf("Error\nMap is not surrounded by walls");
        return (0);
      }
      else if (map[i][j] == 'P')
      {
        (*begin).y = i;
        (*begin).x = j;
      }
      j++;
    }
    i++;
  }
  return (1);
}                  


