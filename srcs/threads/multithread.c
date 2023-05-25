/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:02:22 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 16:26:22 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	partial_render(t_app *a, t_img_data *img, int v_start, int v_stop);
static void	init_thread_images(t_app *a, int i);

/*
	The idea is to split the screen into strips and get each thread to render
	one of them. There is a mutex protecting the diffrent chunks, lock over this
	mutex will be used to
*/
void	multithread_render(t_app *a)
{
	int	i;

	release_render_lock(a);
	usleep(1000);
	get_render_lock(a);
	i = -1;
	while (++i < MRT_THREAD_COUNT)
		mlx_put_image_to_window(a->mlx_instance, a->window,
			a->thread_img[i].img, 0, 0);
}

void	start_threads(t_app *a)
{
	int	i;

	i = -1;
	while (++i < MRT_THREAD_COUNT)
	{
		init_thread_images(a, i);
		if (pthread_mutex_init(&a->render_lock[i], NULL)
			|| pthread_mutex_init(&a->start_lock[i], NULL))
			perror("failed to make mutex!?");
		a->thread_info[i] = (t_ptinfo){i, a, 1, 1};
		if (pthread_create(&a->thread_instance[i], NULL,
				&thread_routine, &a->thread_info[i]))
			perror("failed to start threads!?");
		printf("starting thread %d\n", i);
	}
}

/*
v_start = (MRT_CHUNK_HEIGHT) * me;
TODO: looks like this might need a check for tiny resolutions
fo is info but the norm
*/

void	*thread_routine(void *info_struct)
{
	int			me;
	t_ptinfo	*fo;
	t_app		*a;
	int			v_start;
	int			v_stop;

	fo = (t_ptinfo *)info_struct;
	a = (t_app *)fo->app;
	me = fo->id;
	v_start = (MRT_CHUNK_HEIGHT) * me;
	if (me == MRT_THREAD_COUNT - 1)
		v_stop = HEIGHT;
	else
		v_stop = v_start + (MRT_CHUNK_HEIGHT);
	while (1)
	{
		while (!try_reserve_thread(&a->render_lock[me], &fo->lock, &fo->status))
			usleep(100);
		partial_render(a, &a->thread_img[me], v_start, v_stop);
		fo->status = 1;
		if (try_return_thread(&a->render_lock[me], &fo->lock, &fo->status))
			usleep(100);
		usleep(100);
	}
	return (NULL);
}

static void	partial_render(t_app *a, t_img_data *img, int v_start, int v_stop)
{
	int		u;
	int		v;
	t_ray	ray;
	t_v3	clr;

	u = 0;
	while (u < a->img.width)
	{
		v = v_start;
		if (v != 0)
			v -= 1;
		while (v < v_stop)
		{
			ray = pixel_to_ray(a, u, v);
			clr = draw_ray(a, ray);
			my_mlx_pixel_put(img, u, v, v3_to_col(clr));
			v++;
		}
		u++;
	}
}

static void	init_thread_images(t_app *a, int i)
{
	a->thread_img[i].width = a->img.width;
	a->thread_img[i].height = a->img.height;
	a->thread_img[i].img = mlx_new_image(a->mlx_instance,
			a->img.width, a->img.height);
	if (!a->thread_img[i].img)
		perror("couldn't make mxl image");
	a->thread_img[i].addr = mlx_get_data_addr(a->thread_img[i].img,
			&a->thread_img[i].bits_per_pixel,
			&a->thread_img[i].line_length,
			&a->thread_img[i].endian);
	if (!a->thread_img[i].addr)
		perror("couldn't get mxl addr");
	fill_screen(&a->thread_img[i], MRT_TRANS);
}
