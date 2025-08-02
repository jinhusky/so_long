/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mem_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:58:40 by kationg           #+#    #+#             */
/*   Updated: 2025/08/02 16:52:27 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_grid(char **grid, t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.h)
		free(grid[i++]);
	free(grid);
}

void	destroy_sprite(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->player_right.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_left.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_front.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_back.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->floor.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->collectibles.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->wall.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->exit.img_ptr);
}

void	free_map(t_game *game)
{
	if (game->map.matrix)
		free_grid(game->map.matrix, game);
	if (game->map.array)
		free(game->map.array);
}

void	error_mssg(char *message, t_game *game)
{
	ft_printf("Error\n""%s\n", message);
	if (game->map.matrix)
		free_grid(game->map.matrix, game);
	if (game->map.array)
		free(game->map.array);
	exit(EXIT_FAILURE);
}
