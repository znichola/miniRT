/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:41:42 by znichola          #+#    #+#             */
/*   Updated: 2023/03/29 14:54:31 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "time.h"

void	render_ui(t_app *a)
{
	static clock_t		last_frame_time = 0;
	clock_t				current_frame_time;
	char				fps[100];

	if (last_frame_time == 0)
		last_frame_time = clock();
	current_frame_time = clock();
	sprintf(fps, "fps %.1f\n", 1 /
		((float)(current_frame_time - last_frame_time) / CLOCKS_PER_SEC));
	mlx_string_put(a->mlx_instance, a->window, 5, 15, MRT_WHITE, fps);
	last_frame_time = current_frame_time;
}
