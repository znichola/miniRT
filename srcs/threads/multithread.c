/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:02:22 by znichola          #+#    #+#             */
/*   Updated: 2023/05/20 12:17:39 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	partial_render(t_app *a, t_img_data *img, int v_start, int v_stop);

/*
	The idea is to split the screen into strips and get each thread to render
	one of them. There is a mutex protecting the diffrent chunks, lock over this
	mutex will be used to
*/
void	multithread_render(t_app *a)
{
	int	i;

	// printf(">>>>>>>>>>>> starting rendering threads frame_count:%d\n", count);
	release_render_lock(a);
	usleep(1000);
	get_render_lock(a);
	// printf(">>>>>>>>>>>> finished rendering threads\n");

	/*
		code to add the diffrent chunks of the image together and display them
		with a pixle put. Simples this goes below!?
	*/

	i = -1;
	while (++i < MRT_THREAD_COUNT)
		mlx_put_image_to_window(a->mlx_instance, a->window,
			a->thread_img[i].img, 0, 0);

	// printf(">>>>>>>>>>>> finished rendering to screen\n");
}

void	start_threads(t_app *a)
{
	int	i;

	i = -1;
	while (++i < MRT_THREAD_COUNT)
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
		if (pthread_mutex_init(&a->render_lock[i], NULL) || pthread_mutex_init(&a->start_lock[i], NULL))
			perror("failed to make mutex!?");
		a->thread_info[i] = (t_ptinfo){i, a, 1, 1};
		if (pthread_create(&a->thread_instance[i], NULL, &thread_routine, &a->thread_info[i]))
			perror("failed to start threads!?");
		printf("starting thread %d\n", i);
	}
}

void	*thread_routine(void *info_struct)
{
	int			me = 0;
	t_ptinfo	*info;
	t_app		*a = NULL;
	int			v_start;
	int			v_stop;

	info = (t_ptinfo *)info_struct;
	a = (t_app *)info->app;
	me = info->id;
	v_start = MRT_CHUNK_HEIGHT * me; /* TODO: looks like this might need a check for tiny resolutions */
	if (me == MRT_THREAD_COUNT - 1)
		v_stop = HEIGHT;
	else
		v_stop = v_start + MRT_CHUNK_HEIGHT;
	while(1)
	{
		while(!try_reserve_thread(&a->render_lock[me], &info->lock, &info->status))
			usleep(100);
		// printf("thread %d got render lock\n", me);
		usleep(1000 * (5 - me) + 100);
		partial_render(a, &a->thread_img[me], v_start, v_stop);
		info->status = 1;
		// printf("thread %d reporting in with a finished render!\n", me);
		if (try_return_thread(&a->render_lock[me], &info->lock, &info->status))
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
		while (v < v_stop)
		{
			ray = pixel_to_ray(a, u, v);
			clr = draw_ray(a, ray);
			wrapper_pixel_put(img, u, v, v3_to_col(clr));
			v++;
		}
		u++;
	}
}
