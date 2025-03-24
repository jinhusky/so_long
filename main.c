/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:55:27 by kationg           #+#    #+#             */
/*   Updated: 2025/03/24 13:15:29 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf/src/ft_printf.h"
#include "includes/so_long.h"    
#include "mlx/mlx.h"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    //perror("Error, program only accepts one argument (Usage:./so_long mapfile)");
    //ft_printf("Only accepts one arugment: %s\n", strerror(errno));
    ft_printf("Error: wrong number of arguments. Expected 2, got %d.\n", argc - 1);
    return (EXIT_FAILURE);
  }
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1)
  {
    perror("Error opening file");
    return (EXIT_FAILURE);
  }
  int width = 0, height = 0;
  char * buffer = check_map_size(fd, &width, &height);
  char **map = parsing(width, height, buffer);
 	ft_printf("%s\n", buffer);
  for (int i = 0; i < height; i++)
  {
    ft_printf("%s\n", map[i]);
  }
  if (!check_minimum_asset(buffer))
    return(EXIT_FAILURE);
  t_point begin;
  if (!valid_map(map, width, height, &begin))
    return (EXIT_FAILURE);
  printf("%i %i", begin.y, begin.x);



  t_data data;
  data.mlx_ptr = mlx_init();
  if (!data.mlx_ptr)
    return (1);
  data.win_ptr = mlx_new_window(data.mlx_ptr, 1200, 800, "hi :_)");
  if (!data.win_ptr)
    return (free(data.mlx_ptr), 1);


  int x;
  int y;
  void *tile = mlx_xpm_file_to_image(data.mlx_ptr, "textures/0_Template_Tileset1_A.xpm ", &x, &y);
  mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, tile, 1000 , 600);
  mlx_loop(data.mlx_ptr);
  mlx_destroy_image(data.mlx_ptr, tile);
  mlx_destroy_display(data.mlx_ptr);
  free(data.mlx_ptr);
  return (0);
  
  return (0);
}
