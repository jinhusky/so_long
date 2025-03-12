/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:27:42 by kationg           #+#    #+#             */
/*   Updated: 2025/03/12 10:38:40 by kaijing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"


typedef struct s_point
{
  int x;
  int y;
} t_point;



//the function takes char * data type for file path because the file path is passed as a string
//added to check that it has same width in all rows, to ensure map is rectangled shaped
static void check_map_size(int fd, int *width, int *height)
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
      ft_printf("Error \n MAP IS NOT RECTANGLE");
      return ;
    }
    free(line);
    line = get_next_line(fd);
    (*height)++;
  }
}

//malloc once here (total malloc = 1)
static char **parsing(int width, int height, int fd)
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
  return (res);
}

static int init_map(int fd)
{
  int width = 0, height = 0;
  check_map_size(fd, &width, &height);
  char **tab = parsing(width, height, fd);
  return 1;
}



/*
int main(void)
{
  t_point size;
  t_point begin;
  char **tab = parse_map("map/map1.ber", &size, &begin);

  int fd = open("map/map1.ber", O_RDONLY);
  if (fd == - 1)
  {
    printf("ERROR OPENING FILE");
    return NULL;
  }




}*/

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    ft_printf("Error\n ONLY ACCEPT one argument");
    return(1);
  }
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1)
  {
    ft_printf("Error\n ERROR OPENING FILE");
    return (2);
  }
  init_map(fd);
  

}
