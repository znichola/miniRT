/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:26:04 by znichola          #+#    #+#             */
/*   Updated: 2023/03/20 01:41:30 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void debug_print_held(t_app *a);

int	render_frame(t_app *a)
{
	// static t_v2int old_pos;
	static int change_flag = 1;

	if (getset_settings(MRT_DEBUG_PRINT))
		debug_print_held(a);

	// print_image(a);

	if (scale_property(a, &a->l_origin.x, "mx", e_mouse_left, 1)
		& scale_property(a, &a->l_origin.y, "my", e_mouse_left, 1)
		& scale_property(a, &a->l_origin.z, "my", e_mouse_right, 1)
		& scale_property(a, &a->sp_radius, "ky", e_key_s, 0.2))
		change_flag = 1;

	if (change_flag)
	{
		fill_screen(&a->img, MRT_BLACK);
		render_sphere(a);
		change_flag = 0;
		get_mouse_diff(a, -1);
		print_v3("light", &a->l_origin);
	}
	else
		usleep(100);

	ft_memset(&a->mouse_key_click, 0, sizeof(a->mouse_key_click));
	ft_memset(&a->mouse_key_release, 0, sizeof(a->mouse_key_release));
	ft_memset(&a->keyboard_press, 0, sizeof(a->keyboard_press));
	ft_memset(&a->keyboard_release, 0, sizeof(a->keyboard_release));

	// printf("old(%d, %d) current(%d, %d) diff(%d, %d)\n", a->mouse_pos_old.x, a->mouse_pos_old.y, a->mouse_pos.x, a->mouse_pos.y, a->mouse_pos_old.x - a->mouse_pos.x, a->mouse_pos_old.y - a->mouse_pos.y);

	a->mouse_pos_old = a->mouse_pos;

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
