/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:17:17 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/21 00:18:24 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_app	a;
	t_scene	scene;

	if (ac != 2)
	{
		return 0;
	}

	getset_settings(MRT_LOADING_PRINT | MRT_MULTI_THRED);

	// initialising everything to 0 so we are sure it's all copacetic
	ft_memset(&a, 0, sizeof(t_app));
	// a = (t_app){} // but apparently this also works, who knew?

	ft_putstr_fd("hello raytraced world\n", 1);

	a.mlx_instance = mlx_init();
	a.img.width = WIDTH;
	a.img.height = HEIGHT;

	a.window = mlx_new_window(a.mlx_instance, WIDTH, HEIGHT, "vecTHOR");
	a.img.img = mlx_new_image(a.mlx_instance, WIDTH, HEIGHT);
	a.img.addr = mlx_get_data_addr(a.img.img,
						&a.img.bits_per_pixel,
						&a.img.line_length,
						&a.img.endian);

	/* ------- scene settings ------------- */

	a.a_colour = MRT_RED;
	a.a_ratio = 0.1;
	a.global_ambient = colour_brightness_multi(a.a_colour, a.a_ratio);

	a.c_origin = (t_v3){0, 0, 0};
	a.c_normal = (t_v3){0, 0, 1};
	a.c_fov = 90.0;
	a.c_aspect_ratio = a.img.width / a.img.height;

	a.l_origin = (t_v3){50, 300, 600};
	a.l_colour = MRT_WHITE;
	a.l_brightness = 0.9;

	a.sp_origin = (t_v3){0, 0, 60}; // lefthanded rule?
	a.sp_radius = 50;
	a.sp_colour = MRT_PALE_BLUE;

	a.c_origin = (t_v3){0, 0, 0};
	a.c_normal = v3_unitvec((t_v3){0, 1, 0});
	a.c_viewport_offset = 1;
	a.c_fov = M_PI_2;

	/* ---------- end scene ----------------*/


	mlx_hook(a.window, e_on_destroy, 0, destroy_window, &a);

	// keyboard
	mlx_do_key_autorepeatoff(a.mlx_instance);
	mlx_hook(a.window, e_on_keydown, 0, keyboard_on_press, &a);
	mlx_hook(a.window, e_on_keyup, 0, keyboard_on_release, &a);

	// mouse
	mlx_hook(a.window, e_on_mousemove, 0, mouse_movement_track, &a);
	mlx_hook(a.window, e_on_mouseup , 0, mouse_on_release, &a);
	mlx_mouse_hook(a.window, mouse_on_click, &a);

	// render hookup
	mlx_loop_hook(a.mlx_instance, render_frame, &a);

	mlx_loop(a.mlx_instance);
	return (0);

}
