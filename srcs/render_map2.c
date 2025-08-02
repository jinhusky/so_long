/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:29:47 by kationg           #+#    #+#             */
/*   Updated: 2025/08/02 19:13:21 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	draw_pixel(t_sprite *buffer, int color, int y, int x)
{
	char	*pixel;

	if (color != (int)0xFF000000)
	{
		pixel = buffer->img_addr + ((y * buffer->size_line)
				+ (x *(buffer->bpp / 8)));
		*(unsigned int *)pixel = color;
	}
}

//bpp is 4 (32/8 == 4, 4bytes per pixel) size_line to skip padding 
//img_data + position to move towards the target pixel to avoid byte offset
void	buffer_sprite(t_game *game, t_sprite *sprite, t_point pos)
{
	int		i;
	int		j;
	int		color;
	int		location;
	t_point	temp;

	i = 0;
	while (i < sprite->size.y)
	{
		j = 0;
		while (j < sprite->size.x)
		{
			location = (i * sprite->size_line) + (j * sprite->bpp / 8);
			color = *(unsigned int *)(sprite->img_addr + location);
			temp.y = pos.y + i;
			temp.x = pos.x + j;
			draw_pixel(&game->buffer, color, temp.y, temp.x);
			j++;
		}
		i++;
	}
}
