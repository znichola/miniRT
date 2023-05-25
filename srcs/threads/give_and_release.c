/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   give_and_release.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 00:58:09 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 12:47:06 by znichola         ###   ########.fr       */
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
	while (i < MRT_THREAD_COUNT)
	{
		if (!(mask & (1U << i))
			&& try_return_main(&a->render_lock[i], &a->thread_info[i].lock,
				&a->thread_info[i].status))
			mask |= (1U << i);
		i++;
		if (i == MRT_THREAD_COUNT && (mask & full_mask) != full_mask)
			i = 0;
		usleep(1000);
	}
}

void	get_render_lock(t_app *a)
{
	int					i;
	unsigned int		mask;
	const unsigned int	full_mask = (1U << MRT_THREAD_COUNT) - 1;

	mask = 0;
	i = 0;
	while (i < MRT_THREAD_COUNT)
	{
		if (!(mask & (1U << i))
			&& try_reserve_main(&a->render_lock[i], &a->thread_info[i].lock,
				&a->thread_info[i].status))
		{
			mask |= (1U << i);
		}
		i++;
		if (i == MRT_THREAD_COUNT && (mask & full_mask) != full_mask)
			i = 0;
		usleep(100);
	}
}
