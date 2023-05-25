/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:05:26 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 16:35:32 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	fill_screen(t_img_data *img, int colour)
{
	int		y;
	int		x;
	char	*dst;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			dst = img->addr + (y * img->line_length + x * (
						img->bits_per_pixel / 8));
			*(unsigned int *)dst = colour;
			x++;
		}
		y++;
	}
}
