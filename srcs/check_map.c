/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:18:06 by kationg           #+#    #+#             */
/*   Updated: 2025/08/02 17:51:49 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	check_map_size(t_game *game)
{
	char	*line;
	int		p_width;
	char	*temp;

	game->map.array = ft_strdup("");
	line = get_next_line(game->map.fd);
	p_width = 0;
	while (line)
	{
		if (game->map.h != 0)
			p_width = game->map.w;
		game->map.w = 0;
		temp = game->map.array;
		game->map.array = ft_strjoin(temp, line);
		free(temp);
		while (line[game->map.w] != '\n' && line[game->map.w])
			game->map.w++;
		if (p_width != game->map.w && game->map.h != 0)
		{
			if (game->map.array)
				free(game->map.array);
			free(line);
			error_mssg("Map is Not Rectangle", game);
		}
		free(line);
		line = get_next_line(game->map.fd);
		game->map.h++;
	}
}

static char	**parse_matrix(t_game *game)
{
	int		i;
	int		len;
	int		count;
	char	**grid;

	i = 0;
	count = 0;
	grid = malloc(game->map.h * sizeof(char *));
	while (game->map.array[i])
	{
		len = 0;
		grid[count] = malloc(game->map.w + 1);
		while (game->map.array[i] != '\n' && game->map.array[i])
		{
			i++;
			len++;
		}
		ft_strlcpy(grid[count], game->map.array + i - len, game->map.w + 1);
		count++;
		if (game->map.array[i] == '\n')
			i++;
	}
	return (grid);
}

static void	check_minimum_asset(t_game *game)
{
	int	i;
	int	c;

	i = 0;
	while (game->map.array[i])
	{
		c = game->map.array[i];
		if (!ft_strchr("PCE10\n", c))
			error_mssg("Map has unallowed characters", game);
		if (c == PLAYER)
			game->map.player++;
		else if (c == COLLECTIBLES)
			game->map.collect++;
		else if (c == EXIT)
			game->map.exit++;
		i++;
	}
	if (game->map.player != 1 || game->map.collect < 1
		|| game->map.exit != 1)
		error_mssg("No exit/collectible/player", game);
}

static void	valid_map(t_game *game)
{
	int		i;
	int		j;
	char	**m;

	i = 0;
	m = game->map.matrix;
	while (i < game->map.h)
	{
		j = 0;
		while (j < game->map.w)
		{
			if (m[i][0] != WALL || m[0][j] != WALL
				|| m[game->map.h - 1][j] != WALL
				|| m[i][game->map.w - 1] != WALL)
				error_mssg("Map not surrounded by Walls", game);
			else if (m[i][j] == 'P')
			{
				game->map.starting_p.y = i;
				game->map.starting_p.x = j;
			}
			j++;
		}
		i++;
	}
}

void	check_map(t_game *game)
{
	char	**cpy_grid;
	t_point	s_pos;

	check_map_size(game);
	game->map.matrix = parse_matrix(game);
	check_minimum_asset(game);
	valid_map(game);
	cpy_grid = parse_matrix(game);
	s_pos = game->map.starting_p;
	flood_fill(cpy_grid, game->map.h, game->map.w, s_pos.y, s_pos.x);
	if (check_floodfill(cpy_grid, game))
	{
		free_grid(cpy_grid, game);
		error_mssg("Some exit or collectibles cannot be reached", game);
	}
	free_grid(cpy_grid, game);
}
