/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:27:42 by kationg           #+#    #+#             */
/*   Updated: 2025/03/07 15:21:10 by kaijing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
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
  char **tab;
  return (tab);
  

}

int main(void)
{
  t_point size;
  t_point begin;
  char **tab = parse_map("map/map1.ber", &size, &begin);

}
