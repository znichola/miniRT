/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:26:04 by znichola          #+#    #+#             */
/*   Updated: 2023/05/11 18:36:31 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "float.h"

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
		& scale_property(a, &a->sp_radius, "ky", e_key_s, 0.2)
		& scale_property(a, &a->c_origin.z, "ky", e_key_z, 1)
		& scale_property(a, &a->c_origin.x, "kx", e_key_c, 1)
		& scale_property(a, &a->c_origin.y, "ky", e_key_c, 1)
		& scale_property(a, &a->c_normal.z, "ky", e_key_w, 0.1)
		& scale_property(a, &a->c_normal.x, "kx", e_key_v, 0.1)
		& scale_property(a, &a->c_normal.y, "ky", e_key_v, 0.1)
		& scale_property(a, &a->c_fov, "ky", e_key_f, 0.2))
	{
		change_flag = 1;
		a->c_normal = v3_unitvec(a->c_normal);
	}

	if (change_flag)
	{
		fill_screen(&a->img, MRT_BLACK);
		render_sphere(a);
		change_flag = 0;
		get_mouse_diff(a, -1);
		// print_v3("light", &a->l_origin);
		// print_v3("camera", &a->c_origin);
		// print_v3("normal", &a->c_normal);
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
