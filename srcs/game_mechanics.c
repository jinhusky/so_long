/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mechanics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:11:10 by kationg           #+#    #+#             */
/*   Updated: 2025/08/02 18:50:22 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_boundary(t_game *game, t_point position)
{
	int	y;
	int	x;

	y = position.y;
	x = position.x;
	if (game->map.matrix[y][x] == WALL)
		return (0);
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
	return (1);
}

int	handle_input(int keycode, t_game *game)
{
	t_point	temp;

	temp = game->map.starting_p;
	if (keycode == XK_Escape)
		close_game(game);
	else if (keycode == XK_w)
		up(game, &temp);
	else if (keycode == XK_s)
		down(game, &temp);
	else if (keycode == XK_a)
		left(game, &temp);
	else if (keycode == XK_d)
		right(game, &temp);
	return (0);
}
