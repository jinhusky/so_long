/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:55:27 by kationg           #+#    #+#             */
/*   Updated: 2025/06/04 18:14:23 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/so_long.h"    

static void check_cml_argument(int argc, char *arg, t_game *game)
{
  if (argc > 2)
    error_mssg("Too many arguments, Usage: ./so_long [map file path]", game);
  else if (argc < 2)
    error_mssg("To run game please include the path of map file", game);
  int i = 0;
  char *file_type;
  file_type = arg;
  while (file_type[i] != '.')
    file_type++;
  if (ft_strncmp(".ber", file_type, 5) != 0)
    error_mssg("invalid map file type, only .ber file is accepted", game);
  int fd = open(arg, O_RDONLY);
  if (fd == -1)
    error_mssg("Unable to open map file", game);
  game->map.fd = fd;
}

int main(int argc, char *argv[])
{
  t_game game;
  ft_memset(&game, 0, sizeof(t_game));
  check_cml_argument(argc, argv[1], &game);
  check_map(&game);
  init_mlx(&game);
  load_sprite(&game);
  mlx_loop_hook(game.mlx_ptr, print_game_map, &game);
  mlx_hook(game.win_ptr, 17, 0L, close_game,  &game);
  mlx_key_hook(game.win_ptr, handle_input, &game);
  mlx_loop(game.mlx_ptr);
}
