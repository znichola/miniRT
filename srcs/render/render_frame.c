/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:26:04 by znichola          #+#    #+#             */
/*   Updated: 2023/03/13 17:31:26 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	render_frame(t_app *a)
{
	// printf("[");
	// for (int i = 0; i < MOUSE_KEY_COUNT; i++)
	// 	if (a->mouse_key_held[i])
	// 		printf("%d, ", i);
	// 	else
	// 		printf("-, ");
	// printf("]\n");

	fill_screen(&a->img, MRT_BLACK);

	put_circle_fast(&a->img, 50, (t_v2int){400, 400}, MRT_WHITE);

	mlx_put_image_to_window(a->mlx_instance, a->window, a->img.img, 0, 0);
	usleep(100);
	return (0);
}
