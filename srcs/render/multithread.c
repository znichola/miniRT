/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:02:22 by znichola          #+#    #+#             */
/*   Updated: 2023/03/18 10:12:39 by znichola         ###   ########.fr       */
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
	get_or_release_locks(a, 1);
	/*
		code to add the diffrent chunks of the image together and display them
		with a pixle put. Simples
	*/
	get_or_release_locks(a, 0);
}

void	start_threads(t_app *a)
{
	int	i;

	i = 0;
	while (i < MRT_THREAD_COUNT)
	{
		a->thread_img[i].img = mlx_new_image(a->mlx_instance,
									a->img.width, a->img.height);
		a->thread_img[i].addr = mlx_get_data_addr(a->thread_img[i].img,
									&a->thread_img[i].bits_per_pixel,
									&a->thread_img[i].line_length,
									&a->thread_img[i].endian);
		if (pthread_mutex_init(&a->thread_lock[i], NULL))
			exit(1);
		pthread_mutex_lock(&a->thread_lock[i]);
		if (pthread_create(&a->thread_instance[i], NULL, &thread_routine, (t_ptinfo *){i, a}))
			exit(1);
	}
}

void	*thread_routine(void *info_struct)
{
	static int		me = 0;
	static t_ptinfo	*info;
	static t_app	*a = NULL;

	if (!a)
	{
		info = (t_ptinfo *)info_struct;
		a = (t_app *)info->app;
		me = info->id;
	}
	while(1)
	{
		pthread_mutex_lock(&a->thread_lock[me]);
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
		pthread_mutex_unlock(&a->thread_lock[me]);
		usleep(1000);
	}
}

void	get_or_release_locks(t_app *a, int action)
{
	int	i;

	i = 0;
	if (action)
	{
		while (i < MRT_THREAD_COUNT)
		{
			pthread_mutex_lock(&a->thread_lock[i]);
			i++;
		}
	}
	else
	{
		while (i < MRT_THREAD_COUNT)
		{
			pthread_mutex_unlock(&a->thread_lock[i]);
			i++;
		}
	}
}
