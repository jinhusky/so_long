/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:17:19 by kationg           #+#    #+#             */
/*   Updated: 2025/08/02 19:01:15 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static t_sprite	init_sprite(t_game *game, char *file_path)
{
	t_sprite	sprite;

	sprite.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			file_path, &sprite.size.x, &sprite.size.y);
	if (!sprite.img_ptr)
		error_mssg("Sprite was not found", game);
	sprite.img_addr = mlx_get_data_addr(sprite.img_ptr,
			&sprite.bpp, &sprite.size_line, &sprite.endian);
	return (sprite);
}

void	load_sprite(t_game *game)
{
	game->player_front = init_sprite(game, "assets/character/"
			"11zon_idle-front.xpm");
	game->player_back = init_sprite(game, "assets/character/"
			"11zon_walk-back.xpm");
	game->player_right = init_sprite(game, "assets/character/"
			"11zon_walk-right.xpm");
	game->player_left = init_sprite(game, "assets/character/"
			"11zon_walk-left.xpm");
	game->collectibles = init_sprite(game, "assets/items/key.xpm");
	game->exit = init_sprite(game, "assets/items/exit.xpm");
	game->floor = init_sprite(game, "assets/terrains/ground.xpm");
	game->wall = init_sprite(game, "assets/terrains/wall.xpm");
}

void	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		error_mssg("failed to init mlx ptr", game);
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			game->map.w * IMG_W, game->map.h * IMG_H, "so_long");
	if (!game->win_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		error_mssg("failed to make new mlx window", game);
	}
}

int	close_game(t_game *game)
{
	free_map(game);
	destroy_sprite(game);
	if (game->end_state)
		ft_printf("Victory! %i MOVES made \n", game->moves);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	exit (0);
}
