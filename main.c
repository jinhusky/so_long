/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:55:27 by kationg           #+#    #+#             */
/*   Updated: 2025/04/05 14:02:57 by kationg          ###   ########.fr       */
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

static void map_errors(int err, int fd, char *s)
{
  if (err == 1)
  {
    perror("Unable to open map file");
    exit(1);
  }
  if (err == 2)
  {
    close(fd);
    perror("Map not rectangle");
    if (s)
      free(s);
    exit(1);
  }
  if (err == 3)
  {
    close(fd);
    perror("Map is not valid");
    if (s)
      free(s);
    exit(1);
  }
  if (err == 4)
  {
    close(fd);
    ft_printf("Map is not surrounded by walls");
    if (s)
      free(s);
    exit(1);

  }
}

void check_map_size(t_map *data)
{
  data->map = ft_strdup("");
  char *line = get_next_line(data->fd);
  int p_width = 0;

  while (line)
  {
    if (data->h != 0)
      p_width = data->w;
    data->w = 0;
    data->map = ft_strjoin(data->map, line);
    while (line[data->w] != '\n' && line[data->w])
      data->w++;
    if (p_width != data->w && data->h != 0)
    {
      map_errors(2, data->fd, data->map);
      return;
    }
    free(line);
    line = get_next_line(data->fd);
    data->h++;
  }
}

void parse_matrix(t_map *data)
{
  int i = 0;
  int len = 0;
  int count = 0;

  data->matrix = malloc(data->h *sizeof(char *));
  while (data->map[i])
  {
    len = 0;
    data->matrix[count] = malloc(data->w + 1);
    while (data->map[i] != '\n' && data->map[i])
    {
      i++;
      len++;
    }
    ft_strlcpy(data->matrix[count++], data->map + i - len, data->w + 1);
    i++;
  }
}

void check_minimum_asset(t_map *data)
{
  int i = 0;
  while (data->map[i])
  {
    
    int c = data->map[i];
    if (!ft_strchr("PCE10\n", c))
      map_errors(3, data->fd, data->map);
    if (c == 'P')
      data->player++;
    else if (c == 'C')
      data->collect++;
    else if (c == 'E')
      data->exit++;
    i++;
  }
  if (data->player != 1 || data->collect < 1 || data->exit < 1)
    map_errors(3, data->fd, data->map);
}


static void init_map(t_map *map)
{
    map->fd = -1;
    map->h = 0;
    map->w = 0;
    map->map = NULL;
    map->collect = 0;
    map->exit = 0;
    map->player = 0;
}

void valid_map(t_map *data)
{
  int i = 0;
  int j;
  char **m = data->matrix;
  while (i < data->h)
  {
    j = 0;
    while (j < data->w)
    {
    
      if (m[i][0] != '1' || m[0][j] != '1' || m[data->h - 1][j] != '1' || m[i][data->w - 1] != '1')
        map_errors(4, data->fd, data->map);
      else if (m[i][j] == 'P')
      {
        data->start.y = i;
        data->start.x = j;
      }
      j++;
    }
    i++;
  }
}
static int check_map(char *file_path)
{
  t_map map;
  init_map(&map);
  int fd = open(file_path, O_RDONLY);
  if (fd == -1)
    map_errors(1, fd, NULL);
  map.fd = fd;
  check_map_size(&map);
  parse_matrix(&map);
  check_minimum_asset(&map);
  valid_map(&map);

  return (1);
}

void render_map(void)
{
  t_vars mlx;
  mlx.mlx_ptr = mlx_init();
  mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 1200, 800, "Vicky boi");
}
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    ft_printf("Error :./usage map");
    return (1);
  }

  check_map(argv[1]);
  render_map();

}



