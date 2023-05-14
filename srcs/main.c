/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:17:17 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/14 11:52:57 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	init_mlx_window(t_app *a);

int	main(int ac, char **av)
{
	t_app	a;

	if (ac != 2)
	{
		printf("Error\nExpected filename\n");
		return (1);
	}

	// initialising everything to 0 so we are sure it's all copacetic
	ft_memset(&a, 0, sizeof(t_app));

	getset_app(&a);

	// parse the scene
	if (parse(av[1], &a.s) != 0)
		return (1);

	//some settings!
	getset_settings(MRT_LOADING_PRINT | MRT_MULTI_THRED);

	init_mlx_window(&a);

	load_all_textures(&a);


	a.selected = a.s.objects_list->content;
	print_scene(&a);
	// exit(42);

	if (MRT_THREAD_COUNT > 1)
		start_threads(&a);

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
	mlx_loop_hook(a.mlx_instance, render_world, &a);

	mlx_loop(a.mlx_instance);

	//free the objects lists from our scene
	cleanup_scene(&a.s);

	return (0);
}

static int	init_mlx_window(t_app *a)
{
	a->mlx_instance = mlx_init();
	a->img.width = WIDTH;
	a->img.height = HEIGHT;
	a->window = mlx_new_window(a->mlx_instance, WIDTH, HEIGHT, "vecTHOR");
	a->img.img = mlx_new_image(a->mlx_instance, WIDTH, HEIGHT);
	if (!a->img.img)
		perror("couldn't make mxl image");
	a->img.addr = mlx_get_data_addr(a->img.img, &a->img.bits_per_pixel,
		&a->img.line_length, &a->img.endian);
	if (!a->img.addr)
			perror("couldn't get mxl addr");

	return (0);
}
