/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:17:17 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/13 17:01:08 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main()
{
	t_app	a;

	ft_putstr_fd("hello raytraced world\n", 1);

	// initialising everything to 0 so we are sure it's all copacetic
	ft_memset(&a, 0, sizeof(t_app));
	a.mlx_instance = mlx_init();
	a.img.width = WIDTH;
	a.img.hight = HEIGHT;

	a.window = mlx_new_window(a.mlx_instance, WIDTH, HEIGHT, "vecTHOR");
	a.img.img = mlx_new_image(a.mlx_instance, WIDTH, HEIGHT);
	a.img.addr = mlx_get_data_addr(a.img.img,
						&a.img.bits_per_pixel,
						&a.img.line_length,
						&a.img.endian);

	a.circle = (t_v2int){WIDTH / 2, HEIGHT / 2};

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
