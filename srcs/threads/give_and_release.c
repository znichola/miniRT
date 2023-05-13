/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   give_and_release.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 00:58:09 by znichola          #+#    #+#             */
/*   Updated: 2023/05/13 12:03:04 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	release_render_lock(t_app *a)
{
	int					i;
	unsigned int		mask;
	const unsigned int	full_mask = (1U << MRT_THREAD_COUNT) - 1;

	mask = 0;
	i = 0;
	printf("trying to release render locks\n");
	while (i < MRT_THREAD_COUNT)
	{
		// if (!(mask & (1U << i)) &&
		if (
			 try_return_main(&a->render_lock[i], &a->thread_info[i].lock, &a->thread_info[i].status))
		{
			mask |= (1U << i);
			printf(" -------------------- released render lock %d\n", i);
		}
		i++;
		if (i == MRT_THREAD_COUNT && (mask & full_mask) != full_mask)
			i = 0;
		usleep(1000);
	}
	printf("released render locks\n");
}

void	get_render_lock(t_app *a)
{
	int					i;
	unsigned int		mask;
	const unsigned int	full_mask = (1U << MRT_THREAD_COUNT) - 1;

	mask = 0;
	i = 0;
	printf("trying to get render locks\n");
	while (i < MRT_THREAD_COUNT)
	{
		// if (!(mask & (1U << i)) &&
		if (
			try_reserve_main(&a->render_lock[i], &a->thread_info[i].lock, &a->thread_info[i].status))
		{
			mask |= (1U << i);
			printf(" -------------------- got render lock %d\n", i);
		}
		i++;
		if (i == MRT_THREAD_COUNT && (mask & full_mask) != full_mask)
			i = 0;
		usleep(100);
	}
	printf("got render locks\n");
}
