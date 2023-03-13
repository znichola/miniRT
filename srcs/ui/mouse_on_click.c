/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_on_click.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:21:42 by znichola          #+#    #+#             */
/*   Updated: 2023/03/13 16:42:26 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
