/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement_track.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:18:22 by znichola          #+#    #+#             */
/*   Updated: 2023/03/13 16:17:07 by znichola         ###   ########.fr       */
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
