/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:41:42 by znichola          #+#    #+#             */
/*   Updated: 2023/05/11 15:51:33 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "time.h"

static void	render_fps_ui(t_app *a, t_v2int pos);

void	render_ui(t_app *a)
{
	render_fps_ui(a, (t_v2int){5, 15});
	render_selection_ui(a, (t_v2int){5, 30});
}

static void	render_fps_ui(t_app *a, t_v2int pos)
{
	static clock_t		last_frame_time = 0;
	clock_t				current_frame_time;
	char				fps[100];

	if (last_frame_time == 0)
		last_frame_time = clock();
	current_frame_time = clock();
	sprintf(fps, "fps %.1f", 1 /
		((float)(current_frame_time - last_frame_time) / CLOCKS_PER_SEC));
	mlx_string_put(a->mlx_instance, a->window, pos.x, pos.y, MRT_WHITE, fps);
	last_frame_time = current_frame_time;
}
