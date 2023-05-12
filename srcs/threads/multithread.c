/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:02:22 by znichola          #+#    #+#             */
/*   Updated: 2023/05/13 01:31:01 by znichola         ###   ########.fr       */
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
	static int	count = 0;

	printf(">>>>>>>>>>>>> starting rendering threads frame_count:%d\n", count);
	release_render_lock(a);
	usleep(1000);
	get_start_lock(a);
	/*
		code to add the diffrent chunks of the image together and display them
		with a pixle put. Simples
	*/
	get_render_lock(a);
	release_start_lock(a);

	printf(">>>>>>>>>>>> finished rendering threads\n");
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
		a->thread_img[i].addr = mlx_get_data_addr(a->thread_img[i].img,
									&a->thread_img[i].bits_per_pixel,
									&a->thread_img[i].line_length,
									&a->thread_img[i].endian);
		if (pthread_mutex_init(&a->render_lock[i], NULL) || pthread_mutex_init(&a->start_lock[i], NULL))
		{
			perror("failed to make mutex!?");
			exit(13);
		}
		pthread_mutex_lock(&a->render_lock[i]);
		// pthread_mutex_lock(&a->start_lock[i]);
		a->thread_info[i].id = i;
		a->thread_info[i].app = a;
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

	if (!a)
	{
		info = (t_ptinfo *)info_struct;
		a = (t_app *)info->app;
		me = info->id;
	}
	while(1)
	{
		// printf("thread %d is trying to unlock\n", me);
		pthread_mutex_lock(&a->start_lock[me]);
		usleep(100);
		pthread_mutex_lock(&a->render_lock[me]);
		usleep(100);
		pthread_mutex_unlock(&a->start_lock[me]);
		// printf("thread %d got the unlock\n", me);
		// usleep(50000);
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
		pthread_mutex_unlock(&a->render_lock[me]);
		printf("thread %d reporting in with a finished render!\n", me);
		usleep(1000);
		// break ;
	}
	return (NULL);
}
