/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partial_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:25:59 by znichola          #+#    #+#             */
/*   Updated: 2023/05/13 21:01:34 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	partial_render(t_app *a, t_img_data *img, int v_start, int v_stop)
{
	int		u;
	int		v;
	t_v3	ray;
	t_v3	clr;

	u = 0;
	while (u < a->img.width)
	{
		v = v_start;
		while (v < v_stop)
		{
			ray = pixel_to_ray(a, u, v);
			clr = draw_ray(a, ray);
			// clr = (t_v3){0.5, 0.2, 0.1};
			wrapper_pixel_put(img, u, v, v3_to_col(clr));
			v++;
		}
		u++;
	}
}
