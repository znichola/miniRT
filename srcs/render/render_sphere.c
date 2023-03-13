/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:28:08 by znichola          #+#    #+#             */
/*   Updated: 2023/03/13 21:19:53 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_sphere(t_app *a)
{
	int camera_offset = 50;

	for (int x = - a->img.width / 2; x < a->img.width; x++)
	{
		for (int y = - a->img.height / 2; y < a->img.height; x++)
		{
			t_v3 vec = (t_v3){x, y, camera_offset};
			vec = v3_norm(vec);
		}
	}
}
