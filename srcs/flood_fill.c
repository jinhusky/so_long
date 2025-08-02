/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:14:25 by kationg           #+#    #+#             */
/*   Updated: 2025/08/02 18:21:56 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	flood_fill(char **grid, int y, int x)
{
	grid[y][x] = 'F';
	if (grid[y - 1][x] != WALL && grid[y - 1][x] != 'F')
		flood_fill(grid, y - 1, x);
	if (grid[y + 1][x] != WALL && grid[y + 1][x] != 'F')
		flood_fill(grid, y + 1, x);
	if (grid[y][x - 1] != WALL && grid[y][x - 1] != 'F')
		flood_fill(grid, y, x - 1);
	if (grid[y][x + 1] != WALL && grid[y][x + 1] != 'F')
		flood_fill(grid, y, x + 1);
}

int	check_floodfill(char **grid, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.h)
	{
		j = 0;
		while (j < game->map.w)
		{
			if (ft_strchr("CE", grid[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
