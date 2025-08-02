/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:37:11 by kationg           #+#    #+#             */
/*   Updated: 2025/08/02 18:45:42 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	up(t_game *game, t_point *temp)
{
	temp->y -= 1;
	if (check_boundary(game, *temp))
	{
		game->map.starting_p.y -= 1;
		game->moves++;
		game->player_state = 1;
	}
}

void	down(t_game *game, t_point *temp)
{
	temp->y += 1;
	if (check_boundary(game, *temp))
	{
		game->map.starting_p.y += 1;
		game->moves++;
		game->player_state = 0;
	}
}

void	left(t_game *game, t_point *temp)
{
	temp->x -= 1;
	if (check_boundary(game, *temp))
	{
		game->map.starting_p.x -= 1;
		game->moves++;
		game->player_state = 2;
	}
}

void	right(t_game *game, t_point *temp)
{
	temp->x += 1;
	if (check_boundary(game, *temp))
	{
		game->map.starting_p.x += 1;
		game->moves++;
		game->player_state = 3;
	}
}
