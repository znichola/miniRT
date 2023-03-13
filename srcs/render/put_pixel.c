/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:05:26 by znichola          #+#    #+#             */
/*   Updated: 2023/03/13 17:25:59 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int offset = (y * line_length + x * (bits_per_pixel / 8));
void	my_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > img->width || y > img->hight)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// fast aproximative algo from stackoverflow
void	put_circle_fast(t_img_data *img, int r, t_v2int center, int colour)
{
	int	y;
	int	x;

	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if (x * x + y * y <= r * r)
				my_mlx_pixel_put(img, center.x + x, center.y + y, colour);
			x++;
		}
		y++;
	}
}

void	fill_screen(t_img_data *img, int colour)
{
	int		i;

	i = 0;
	while (i < img->width * img->hight * 4)
		img->addr[i++] = (unsigned int)colour;
}
