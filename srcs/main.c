/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:17:17 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/29 14:50:45 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_app(t_app *a, int argc, char **argv);
static int	init_mlx_window(t_app *a);
static void	init_hooks(t_app *a);

int	main(int ac, char **av)
{
	t_app	a;

	init_app(&a, ac, av);
	init_hooks(&a);
	return (0);
}

static void	init_app(t_app *a, int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\nExpected filename\n");
		exit(1);
	}
	ft_memset(a, 0, sizeof(t_app));
	getset_app(a);
	if (parse(argv[1], &a->s) != 0)
		exit(2);
	getset_settings(MRT_LOADING_PRINT | MRT_MULTI_THRED);
	init_mlx_window(a);
	load_all_textures(a);
	a->cam_passthrough.type = e_camera;
	a->cam_passthrough.object.c = a->s.camera;
	a->selected = &a->cam_passthrough;
	print_scene(a);
	start_threads(a);
}

static void	init_hooks(t_app *a)
{
	mlx_hook(a->window, e_on_destroy, 0, destroy_window, a);
	mlx_do_key_autorepeatoff(a->mlx_instance);
	mlx_hook(a->window, e_on_keydown, 0, keyboard_on_press, a);
	mlx_hook(a->window, e_on_keyup, 0, keyboard_on_release, a);
	mlx_hook(a->window, e_on_mousemove, 0, mouse_movement_track, a);
	mlx_hook(a->window, e_on_mouseup, 0, mouse_on_release, a);
	mlx_mouse_hook(a->window, mouse_on_click, a);
	mlx_loop_hook(a->mlx_instance, render_world, a);
	mlx_loop(a->mlx_instance);
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
