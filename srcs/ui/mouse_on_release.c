/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_on_release.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:19:00 by znichola          #+#    #+#             */
/*   Updated: 2023/03/13 16:42:23 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
