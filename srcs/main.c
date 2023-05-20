/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:17:17 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/20 19:19:02 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	init_mlx_window(t_app *a);

void	tests(t_app *a)
{
	{
		printf("Camera transformation\n");
		// 200 * 125 at pi/2
		t_camera *c = &a->s.camera;
		printf("fov         %.4f\n", c->fov);
		printf("half_width  %.1f\n", c->half_width);
		printf("half_height %.1f\n", c->half_height);
		printf("pix size 0.01 : %.4f\n", c->pixel_size);
	}
	{
		t_v3	from = (t_v3){0, 0, 8};
		t_v3	to = (t_v3){0, 0, 0};
		t_v3	up = (t_v3){0, 1, 0};
		t_m4	m = view_transform(from, to, up);

		printf("View Transformation\n");
		print_m4(m);
	}
	{
		t_v3	from = (t_v3){1, 3, 2};
		t_v3	to = (t_v3){4, -2, 8};
		t_v3	up = (t_v3){1, 1, 0};
		t_m4	m = view_transform(from, to, up);

		printf("View Transformation\n");
		print_m4(m);
	}
	exit(42);
}

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

	// tests(&a);

	init_mlx_window(&a);

	load_all_textures(&a);

	a.cam_passthrough.type = e_camera;
	a.cam_passthrough.object.c = a.s.camera;

	a.selected = &a.cam_passthrough;

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
