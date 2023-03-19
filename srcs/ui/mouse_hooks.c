/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:18:22 by znichola          #+#    #+#             */
/*   Updated: 2023/03/19 11:49:33 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_movement_track(int x, int y, t_app *a)
{
	a->mouse_pos.x = x;
	a->mouse_pos.y = y;
	// printf("new mouse_pos recorded (%d, %d)\n", x, y);
	return (0);
}

int	mouse_on_click(int action, int x, int y, t_app *a)
{
	(void)x;
	(void)y;
	if (action >= 0 && action < MOUSE_KEY_COUNT)
	{
		// printf("click action : %d\n", action);
		a->mouse_key_click[action] = 1;
		a->mouse_key_held[action] = 1;
	}
	return (0);
}

int	mouse_on_release(int action, int x, int y, t_app *a)
{
	(void)x;
	(void)y;
	if (action >= 0 && action < MOUSE_KEY_COUNT)
	{
		// printf("release action : %d\n", action);
		a->mouse_key_release[action] = 1;
		a->mouse_key_held[action] = 0;
	}
	return (0);
}
