/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:26:04 by znichola          #+#    #+#             */
/*   Updated: 2023/03/17 13:10:34 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void debug_print_held(t_app *a);

int	render_frame(t_app *a)
{
	static t_v2int old_pos;
	static int change_flag = 1;

	debug_print_held(a);

	// for (int x = 0; x < a->img.width; x++)
	// 	for (int y = 0; y < a->img.height; y++)
	// 		my_mlx_pixel_put(&a->img, x, y, moon_texture(a, x, y));
	// mlx_put_image_to_window(a->mlx_instance, a->window, a->img.img, 0, 0);

	// usleep(100000);
	// return 0;

	if (a->mouse_key_click[e_mouse_left])
		old_pos = a->mouse_pos;
	else if (a->mouse_key_held[e_mouse_left])
	{
		// printf("inhere\n");
		float	*scale_a = &a->l_origin.y;
		float	*scale_b = &a->l_origin.x;
		*scale_a += ((double)old_pos.y - a->mouse_pos.y) * 0.5;
		*scale_b += ((double)old_pos.x - a->mouse_pos.x) * 0.5;
		// printf("modified to (%f, %f)\n", *scale_a, *scale_b);
		// print_v3("light", &a->l_origin);

		old_pos = a->mouse_pos;
		// if (*scale < 0)
		// 	*scale = 0;
		// if (*scale > a->img.height / 2)
		// 	*scale = a->img.height - 1;
		// if (*scale > a->img.width / 2)
		// 	*scale = a->img.width - 1;
		change_flag = 1;
	}

	if (change_flag)
	{
		fill_screen(&a->img, MRT_BLACK);
		render_sphere(a);
		change_flag = 0;
	}
	else
		usleep(100);

	ft_memset(&a->mouse_key_click, 0, sizeof(a->mouse_key_click));
	ft_memset(&a->mouse_key_release, 0, sizeof(a->mouse_key_release));
	mlx_put_image_to_window(a->mlx_instance, a->window, a->img.img, 0, 0);
	// exit(0);
	return (0);
}



static void debug_print_held(t_app *a)
{
	printf("[");
	for (int i = 1; i < MOUSE_KEY_COUNT; i++)
	{
		if (a->mouse_key_held[i])
			printf("%d", i);
		else
			printf("-");
		if (i < MOUSE_KEY_COUNT - 1)
			printf(", ");

	}
	printf("]\n");
}
