/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:41:42 by znichola          #+#    #+#             */
/*   Updated: 2023/05/13 21:23:20 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "time.h"

// static void	render_fps_ui(t_app *a, t_v2int pos);
static void	render_fps_ui2(t_app *a, t_v2int pos);

void	render_ui(t_app *a)
{
	render_fps_ui2(a, (t_v2int){5, 15});
	render_selection_ui(a, (t_v2int){5, 30});

	ft_memset(&a->mouse_key_click, 0, sizeof(a->mouse_key_click));
	ft_memset(&a->mouse_key_release, 0, sizeof(a->mouse_key_release));
	ft_memset(&a->keyboard_press, 0, sizeof(a->keyboard_press));
	ft_memset(&a->keyboard_release, 0, sizeof(a->keyboard_release));
}

// /*
// 	this is a measure of cpu time, with multithreading
// 	we burn cpu time super duper quickly!
// */
// static void	render_fps_ui(t_app *a, t_v2int pos)
// {
// 	static clock_t		last_frame_time = 0;
// 	clock_t				current_frame_time;
// 	char				fps[100];

// 	if (last_frame_time == 0)
// 		last_frame_time = clock();
// 	current_frame_time = clock();
// 	sprintf(fps, "fps %.1f", 1 /
// 		((float)(current_frame_time - last_frame_time) / CLOCKS_PER_SEC));
// 	mlx_string_put(a->mlx_instance, a->window, pos.x, pos.y, MRT_WHITE, fps);
// 	last_frame_time = current_frame_time;
// }

/*
	this is a measure of wall clock time and supposedly more accurate
*/
static void	render_fps_ui2(t_app *a, t_v2int pos)
{
	static struct timespec		last_frame_time;
	struct timespec				current_frame_time;
	char						fps[100];
	double						elapsed;

	clock_gettime(CLOCK_MONOTONIC, &current_frame_time);
	elapsed = (current_frame_time.tv_sec - last_frame_time.tv_sec);
	elapsed += (current_frame_time.tv_nsec - last_frame_time.tv_nsec) / 1000000000.0;
	sprintf(fps, "fps %.1f", (float)(elapsed) * 100);
	mlx_string_put(a->mlx_instance, a->window, pos.x, pos.y, MRT_WHITE, fps);
	last_frame_time = current_frame_time;
}
