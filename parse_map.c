/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:27:42 by kationg           #+#    #+#             */
/*   Updated: 2025/03/10 00:25:43 by kaijing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line/get_next_line.h"
#include "so_long.h"

typedef struct s_point
{
  int x;
  int y;
} t_point;



//the function takes char * data type for file path because the file path is passed as a string
char **parse_map(char *file_path, t_point *size, t_point *begin)
{
  int fd = open(file_path, O_RDONLY);
  if (fd == - 1)
  {
    printf("ERROR OPENING FILE");
    return NULL;
  }
  char *line = get_next_line(fd);
  int width = 0, height = 0;
  while (line)
  {
    width = 0;
    while (line[width] != '\n' && line[width] )
    {
      width++;
    }
    free(line);
    line = get_next_line(fd);
    height++;
  }
 char **tab = malloc(height * sizeof(char *));

  return tab;
  
  
  

}

int main(void)
{
  t_point size;
  t_point begin;
  char **tab = parse_map("map/map1.ber", &size, &begin);

}
