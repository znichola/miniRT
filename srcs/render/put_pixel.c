/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:05:26 by znichola          #+#    #+#             */
/*   Updated: 2023/05/13 20:45:33 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	wrapper_pixel_put(t_img_data *img, int x, int y, int colour)
{
	// x += img->width / 2;
	// y += img->height / 2;
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
	int		y;
	int 	x;
	char	*dst;

// 	while (i < img->width * img->height * 4)
// 		img->addr[i++] = (unsigned int)colour;

	y = 0;
	while (y < img->height)
	{

		x = 0;
		while (x < img->width)
		{
			dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
			*(unsigned int *)dst = colour;
			x++;
		}
		y++;
	}

}

// https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
void	put_line(t_img_data *img, t_v2int p1, t_v2int p2)
{
	int	dx = abs(p2.x - p1.x);
	int	dy = abs(p2.y - p1.y);

	int	sx = p1.x < p2.x ? 1 : -1;
	int	sy = p1.y < p2.y ? 1 : -1;

	int	err = (dx > dy ? dx : -dy) / 2;
	int	e2;

	while (1)
	{
		my_mlx_pixel_put(img, p1.x, p1.y, MRT_BRICK);
		if (p1.x == p2.x && p1.y == p2.y)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			p1.x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			p1.y += sy;
		}
	}
}
