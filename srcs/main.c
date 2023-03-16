/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:17:17 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/16 14:09:44 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main()
{
	t_app	a;

	// a = (t_app){}
	ft_putstr_fd("hello raytraced world\n", 1);

	// initialising everything to 0 so we are sure it's all copacetic
	ft_memset(&a, 0, sizeof(t_app));
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

	a.a_colour = MRT_PALE_BLUE;
	a.a_ratio = 0.1;
	a.global_ambient = colour_brightness_multi(a.a_colour, a.a_ratio);

	a.c_origin = (t_v3){0, 0, 0};
	a.c_normal = (t_v3){0, 0, 1};
	a.c_fov = 90.0;

	a.l_origin = (t_v3){50, 300, 200};
	a.l_colour = MRT_WHITE;
	a.l_brightness = 0.5;

	a.sp_origin = (t_v3){0, 0, 80}; // lefthanded rule?
	a.sp_radius = 50;
	a.sp_colour = MRT_BRICK;

	/* ---------- end scene ----------------*/


	mlx_hook(a.window, e_on_destroy, 0, destroy_window, &a);

	// mouse
	mlx_hook(a.window, e_on_mousemove, 0, mouse_movement_track, &a);
	mlx_hook(a.window, e_on_mouseup , 0, mouse_on_release, &a);
	mlx_mouse_hook(a.window, mouse_on_click, &a);

	// keyboard
	mlx_key_hook(a.window, keyboard_press, &a);

	// render hookup
	mlx_loop_hook(a.mlx_instance, render_frame, &a);

	mlx_loop(a.mlx_instance);
	return (0);
}
