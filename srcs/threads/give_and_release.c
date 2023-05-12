/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   give_and_release.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 00:58:09 by znichola          #+#    #+#             */
/*   Updated: 2023/05/13 01:23:10 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_render_lock(t_app *a)
{
	int	i;

	i = 0;
	// printf("trying to get render locks\n");
	while (i < MRT_THREAD_COUNT)
	{
		if (pthread_mutex_lock(&a->render_lock[i]))
		{
			char s[100];
			sprintf(s, "mutex error wih :%d ", i);
			perror(s);
		}
		// printf(" -------------------- got render lock %d\n", i);
		i++;
	}
	// printf("got render locks\n");
}

void	release_render_lock(t_app *a)
{
	int	i;

	i = 0;
	// printf("trying to release render locks\n");
	while (i < MRT_THREAD_COUNT)
	{
		if (pthread_mutex_unlock(&a->render_lock[i]))
		{
			char s[100];
			sprintf(s, "mutex error wih :%d ", i);
			perror(s);
		}
		// printf(" --------------- released render lock %d\n", i);
		i++;
	}
	// printf("released render locks\n");
}

void	get_start_lock(t_app *a)
{
	int	i;

	i = 0;
	// printf("trying to get start locks\n");
	while (i < MRT_THREAD_COUNT)
	{
		if (pthread_mutex_lock(&a->start_lock[i]))
		{
			char s[100];
			sprintf(s, "mutex error wih :%d ", i);
			perror(s);
		}
		// printf(" -------------------- got start lock %d\n", i);
		i++;
	}
	// printf("got start locks\n");
}

void	release_start_lock(t_app *a)
{
	int	i;

	i = 0;
	// printf("trying to release start locks\n");
	while (i < MRT_THREAD_COUNT)
	{
		if (pthread_mutex_unlock(&a->start_lock[i]))
		{
			char s[100];
			sprintf(s, "mutex error wih :%d ", i);
			perror(s);
		}
		// printf(" --------------- released start lock %d\n", i);
		i++;
	}
	// printf("released start locks\n");
}
