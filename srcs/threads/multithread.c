/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:02:22 by znichola          #+#    #+#             */
/*   Updated: 2023/05/13 15:50:51 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	The idea is to split the screen into strips and get each thread to render
	one of them. There is a mutex protecting the diffrent chunks, lock over this
	mutex will be used to
*/
void	multithread_render(t_app *a)
{
	int			i;
	static int	count = 0;

	printf(">>>>>>>>>>>> starting rendering threads frame_count:%d\n", count);
	release_render_lock(a);
	usleep(1000);
	/*
		code to add the diffrent chunks of the image together and display them
		with a pixle put. Simples this goes below!?
	*/
	get_render_lock(a);
	printf(">>>>>>>>>>>> finished rendering threads\n");

	i = -1;
	while (++i < MRT_THREAD_COUNT)
	{
		put_circle_fast(&a->thread_img[i], 10, (t_v2int){300, 40 + i * 40}, MRT_BLUE);
		mlx_put_image_to_window(a->mlx_instance,
			a->window, a->thread_img[i].img, 0, 0);
		break ;
	}

	printf(">>>>>>>>>>>> finished rendering to screen\n");

	count++;
}

void	start_threads(t_app *a)
{
	int	i;

	i = -1;
	printf("starting %d threads\n", MRT_THREAD_COUNT);
	while (++i < MRT_THREAD_COUNT)
	{
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
		if (pthread_mutex_init(&a->render_lock[i], NULL) || pthread_mutex_init(&a->start_lock[i], NULL))
		{
			perror("failed to make mutex!?");
			exit(13);
		}
		a->thread_info[i].id = i;
		a->thread_info[i].app = a;
		a->thread_info[i].lock = 1;
		if (pthread_create(&a->thread_instance[i], NULL, &thread_routine, &a->thread_info[i]))
		{
			perror("failed to start threads!?");
			exit(13);
		}
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
		/*
			code to calculate the rendering for the portion of the image
			assigned to this thread. it's width is a.img.width and
			it's hight is calculated with:

			start:
			a.img.hight / MRT_THREAD_COUNT * (me)

			end:
			a.img.hight / MRT_THREAD_COUNT * (me + 1);

			the image is the same dimentions as the screen
			but only this poriton get's calculated;
		*/
		if (me == 2)
			partial_render(a, &a->img, v_start, v_stop);
		// partial_render(a, &a->thread_img[me], v_start, v_stop);
		info->status = 1;
		printf("thread %d reporting in with a finished render!\n", me);
		if (try_return_thread(&a->render_lock[me], &info->lock, &info->status))
			usleep(100);
		usleep(100);
	}
	return (NULL);
}
