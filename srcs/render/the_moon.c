/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_moon.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:03:25 by znichola          #+#    #+#             */
/*   Updated: 2023/03/18 16:11:20 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	moon_texture(t_app *app, int x, int y)
{
	static t_img_data	moon = {0};
	static char			file_name[] = "doc/moon_hieght_map.xpm";

	if (moon.img == NULL)
	{
		if (getset_settings(MRT_LOADING_PRINT))
			printf("loading %s .. ", file_name);
		moon.width = 1024;
		moon.height = 512;
		moon.img = mlx_xpm_file_to_image(&app->mlx_instance,
							file_name, &moon.width, &moon.height);
		if (moon.img == NULL)
		{
			perror("	failed to load image : ");
			exit(0);
		}
		moon.addr = mlx_get_data_addr(moon.img,
						&moon.bits_per_pixel,
						&moon.line_length,
						&moon.endian);
		if (getset_settings(MRT_LOADING_PRINT))
			printf("	loaded  bpp:%d h:%d w:%d len:%d\n",
				moon.bits_per_pixel, moon.height, moon.width, moon.line_length);
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
	static t_img_data	moon = {0};
	static char			file_name[] = "doc/earth/continents.xpm";

	if (moon.img == NULL)
	{
		if (getset_settings(MRT_LOADING_PRINT))
			printf("loading %s .. ", file_name);
		moon.width = 1024;
		moon.height = 512;
		moon.img = mlx_xpm_file_to_image(&app->mlx_instance,
							file_name, &moon.width, &moon.height);
		if (moon.img == NULL)
		{
			perror("	failed to load image : ");
			exit(0);
		}
		moon.addr = mlx_get_data_addr(moon.img,
						&moon.bits_per_pixel,
						&moon.line_length,
						&moon.endian);
		if (getset_settings(MRT_LOADING_PRINT))
			printf("	loaded  bpp:%d h:%d w:%d len:%d\n",
				moon.bits_per_pixel, moon.height, moon.width, moon.line_length);
	}
	if (x < 0 || y < 0 || x > moon.width - 1 || y > moon.height - 1)
	{
		// printf("tried to go out of bounds (%d, %d)\n", x, y);
		return (MRT_PINK);
	}
	return *(unsigned int *)(moon.addr + (y * moon.line_length + x * (moon.bits_per_pixel / 8)));
}

int	earth_bmp_texture(t_app *app, int x, int y)
{
	static t_img_data	moon = {0};
	static char			file_name[] = "doc/earth/elev_bump.xpm";

	if (moon.img == NULL)
	{
		if (getset_settings(MRT_LOADING_PRINT))
			printf("loading %s .. ", file_name);
		moon.width = 1024;
		moon.height = 512;
		moon.img = mlx_xpm_file_to_image(&app->mlx_instance,
							file_name, &moon.width, &moon.height);
		if (moon.img == NULL)
		{
			perror("	failed to load image : ");
			exit(0);
		}
		moon.addr = mlx_get_data_addr(moon.img,
						&moon.bits_per_pixel,
						&moon.line_length,
						&moon.endian);
		if (getset_settings(MRT_LOADING_PRINT))
			printf("	loaded  bpp:%d h:%d w:%d len:%d\n",
				moon.bits_per_pixel, moon.height, moon.width, moon.line_length);
	}
	if (x < 0 || y < 0 || x > moon.width - 1 || y > moon.height - 1)
	{
		// printf("tried to go out of bounds (%d, %d)\n", x, y);
		return (MRT_PINK);
	}
	return *(unsigned int *)(moon.addr + (y * moon.line_length + x * (moon.bits_per_pixel / 8)));
}

int	earth_nightlight_texture(t_app *app, int x, int y)
{
	static t_img_data	moon = {0};
	static char			file_name[] = "doc/earth/night_lights.xpm";

	if (moon.img == NULL)
	{
		if (getset_settings(MRT_LOADING_PRINT))
			printf("loading %s .. ", file_name);
		moon.width = 1024;
		moon.height = 512;
		moon.img = mlx_xpm_file_to_image(&app->mlx_instance,
							file_name, &moon.width, &moon.height);
		if (moon.img == NULL)
		{
			perror("	failed to load image : ");
			exit(0);
		}
		moon.addr = mlx_get_data_addr(moon.img,
						&moon.bits_per_pixel,
						&moon.line_length,
						&moon.endian);
		if (getset_settings(MRT_LOADING_PRINT))
			printf("	loaded  bpp:%d h:%d w:%d len:%d\n",
				moon.bits_per_pixel, moon.height, moon.width, moon.line_length);
	}
	if (x < 0 || y < 0 || x > moon.width - 1 || y > moon.height - 1)
	{
		// printf("tried to go out of bounds (%d, %d)\n", x, y);
		return (MRT_PINK);
	}
	return *(unsigned int *)(moon.addr + (y * moon.line_length + x * (moon.bits_per_pixel / 8)));
}

// t_v3	bmp_deform_vector(t_app *a, int x, int y, t_v3 norm)
// {
// 	earth_bmp_texture(a, x, y);
// }
