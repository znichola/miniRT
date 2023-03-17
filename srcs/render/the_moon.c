/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_moon.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:03:25 by znichola          #+#    #+#             */
/*   Updated: 2023/03/17 12:33:42 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	moon_texture(t_app *app, int x, int y)
{
	static t_img_data	moon = {0};


	if (moon.img == NULL)
	{
		moon.width = 1024;
		moon.height = 512;
		moon.img = mlx_xpm_file_to_image(&app->mlx_instance,
							"doc/moon_hieght_map.xpm", &moon.width, &moon.height);
		if (moon.img == NULL)
		{
			perror("failed to load image : ");
			exit(0);
		}
		moon.addr = mlx_get_data_addr(moon.img,
						&moon.bits_per_pixel,
						&moon.line_length,
						&moon.endian);
	printf("\nloaded moon texture with these setting\n");
	printf("height:%d\nwidth:%d\nendian:%d\n", moon.height, moon.width, moon.endian);
	printf("bpp:%d\nling_length:%d\nendian:%d\n", moon.bits_per_pixel, moon.line_length, moon.endian);
	printf("adder len:%ld\n\n", ft_strlen(moon.addr));
	}
	if (x < 0 || y < 0 || x > moon.width - 1 || y > moon.height - 1)
	{
		// printf("tried to go out of bounds (%d, %d)\n", x, y);
		return (MRT_PINK);
	}
	return *(unsigned int *)(moon.addr + (y * moon.line_length + x * (moon.bits_per_pixel / 8)));
}

//https://www.shadedrelief.com/natural3/pages/clouds.html

int	earth_texture(t_app *app, int x, int y)
{
	static t_img_data	earth = {0};


	if (earth.img == NULL)
	{
		// moon.width = 3071;
		// moon.height = 1536;
		earth.img = mlx_xpm_file_to_image(&app->mlx_instance,
							"doc/earth/continents.xpm", &earth.width, &earth.height);
		if (earth.img == NULL)
		{
			perror("failed to load image : ");
			exit(0);
		}
		earth.addr = mlx_get_data_addr(earth.img,
						&earth.bits_per_pixel,
						&earth.line_length,
						&earth.endian);
	printf("\nloaded continents texture with these setting\n");
	printf("height:%d\nwidth:%d\nendian:%d\n", earth.height, earth.width, earth.endian);
	printf("bpp:%d\nling_length:%d\nendian:%d\n", earth.bits_per_pixel, earth.line_length, earth.endian);
	printf("adder len:%ld\n\n", ft_strlen(earth.addr));
	}
	if (x < 0 || y < 0 || x > earth.width - 1 || y > earth.height - 1)
	{
		// printf("tried to go out of bounds (%d, %d)\n", x, y);
		return (MRT_PINK);
	}
	return *(unsigned int *)(earth.addr + (y * earth.line_length + x * (earth.bits_per_pixel / 8)));
}

int	earth_bmp_texture(t_app *app, int x, int y)
{
	static t_img_data	earth = {0};


	if (earth.img == NULL)
	{
		// moon.width = 3071;
		// moon.height = 1536;
		earth.img = mlx_xpm_file_to_image(&app->mlx_instance,
							"doc/earth/elev_bump.xpm", &earth.width, &earth.height);
		if (earth.img == NULL)
		{
			perror("failed to load image : ");
			exit(0);
		}
		earth.addr = mlx_get_data_addr(earth.img,
						&earth.bits_per_pixel,
						&earth.line_length,
						&earth.endian);
	printf("\nloaded elev_bump texture with these setting\n");
	printf("height:%d\nwidth:%d\nendian:%d\n", earth.height, earth.width, earth.endian);
	printf("bpp:%d\nling_length:%d\nendian:%d\n", earth.bits_per_pixel, earth.line_length, earth.endian);
	printf("adder len:%ld\n\n", ft_strlen(earth.addr));
	}
	if (x < 0 || y < 0 || x > earth.width - 1 || y > earth.height - 1)
	{
		// printf("tried to go out of bounds (%d, %d)\n", x, y);
		return MRT_PINK;
	}
	return *(unsigned int *)(earth.addr + (y * earth.line_length + x * (earth.bits_per_pixel / 8)));
}

int	earth_nightlight_texture(t_app *app, int x, int y)
{
	static t_img_data	earth = {0};


	if (earth.img == NULL)
	{
		// moon.width = 3071;
		// moon.height = 1536;
		earth.img = mlx_xpm_file_to_image(&app->mlx_instance,
							"doc/earth/night_lights.xpm", &earth.width, &earth.height);
		if (earth.img == NULL)
		{
			perror("failed to load image : ");
			exit(0);
		}
		earth.addr = mlx_get_data_addr(earth.img,
						&earth.bits_per_pixel,
						&earth.line_length,
						&earth.endian);
	printf("\nloaded night_lights texture with these setting\n");
	printf("height:%d\nwidth:%d\nendian:%d\n", earth.height, earth.width, earth.endian);
	printf("bpp:%d\nling_length:%d\nendian:%d\n", earth.bits_per_pixel, earth.line_length, earth.endian);
	printf("adder len:%ld\n\n", ft_strlen(earth.addr));
	}
	if (x < 0 || y < 0 || x > earth.width - 1 || y > earth.height - 1)
	{
		// printf("tried to go out of bounds (%d, %d)\n", x, y);
		return (MRT_PINK);
	}
	return *(unsigned int *)(earth.addr + (y * earth.line_length + x * (earth.bits_per_pixel / 8)));
}
