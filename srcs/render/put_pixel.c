/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:05:26 by znichola          #+#    #+#             */
/*   Updated: 2023/03/14 00:14:35 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	wrapper_pixel_put(t_img_data *img, int x, int y, int colour)
{
	x += img->width / 2;
	y += img->height / 2;
	my_mlx_pixel_put(img, x, y, colour);
}


// int offset = (y * line_length + x * (bits_per_pixel / 8));
void	my_mlx_pixel_put(t_img_data *img, int x, int y, int colour)
{
	char	*dst;

	if (x < 0 || y < 0 || x > img->width - 1 || y > img->height - 1)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	if (colour >= MRT_BLACK && colour <= MRT_WHITE)
		*(unsigned int *)dst = colour;
	else
		*(unsigned int *)dst = MRT_PINK;
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
	while (i < img->width * img->height * 4)
		img->addr[i++] = (unsigned int)colour;
}
