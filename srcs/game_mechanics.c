/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mechanics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:11:10 by kationg           #+#    #+#             */
/*   Updated: 2025/06/04 18:14:13 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int check_boundary(t_game *game, t_point position)
{
  int y = position.y;
  int x = position.x;
  if (game->map.matrix[y][x] == WALL)
    return 0;
  else if (game->map.matrix[y][x] == COLLECTIBLES)
  {
    game->map.collect -= 1;
    game->map.matrix[y][x] = FLOOR;
    if (game->map.collect == 0)
      game->end_state = 1;
  }
  else if (game->map.matrix[y][x] == EXIT && game->end_state)
  {
    game->moves++;
    close_game(game);
  }
  return 1;
}

int handle_input(int keycode, t_game *game)
{
  t_point temp = game->map.starting_p;
  
  if (keycode == XK_Escape)
    close_game(game);
  else if (keycode == XK_w)
  {
    temp.y -= 1;
    if (check_boundary(game, temp))
    {
      game->map.starting_p.y -= 1;
      game->moves++;
      game->player_state = 1;
    }
  } 
  else if (keycode == XK_s)
  {
    temp.y += 1;
    if (check_boundary(game, temp))
    {
      game->map.starting_p.y += 1;
      game->moves++;
      game->player_state = 0;
    }
  }

  else if (keycode == XK_a)
  {
    temp.x -= 1;
    if (check_boundary(game, temp))
    {
      game->map.starting_p.x -= 1;
      game->moves++;
      game->player_state = 2;
    }
  }
  else if (keycode == XK_d)
  {
    temp.x += 1;
    if (check_boundary(game, temp))
    {
      game->map.starting_p.x += 1;
      game->moves++;
      game->player_state = 3;
    }
  }
  return (0);
}

