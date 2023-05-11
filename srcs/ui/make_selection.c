/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_selection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:13:28 by znichola          #+#    #+#             */
/*   Updated: 2023/05/11 22:39:42 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int	screen_select(t_app *a)
{
	t_v3			ray;
	t_object		*obj;
	t_intersection	i;

	ray = pixel_to_ray(a, a->mouse_pos.x, a->mouse_pos.y);
	obj = find_poi(&a->s, ray, a->s.camera.position, &i);
	if (obj)
	{
		a->selected = obj;
		return (1);
	}
	return (0);
}

void	modify_v3(t_app *a, t_v3 *p, int key)
{
	if (!p)
		return ;
	scale_property(a, &p->x, "kx", key, 0.05f);
	scale_property(a, &p->y, "ky", key, 0.05f);
}

void	modify_v3_unitvec(t_app *a, t_v3 *p, int key)
{
	if (!p)
		return ;
	scale_property(a, &p->x, "kx", key, 0.001f);
	scale_property(a, &p->y, "ky", key, 0.001f);
	*p = v3_unitvec(*p);
}

void	modify_v3_colour(t_app *a, t_v3 *p, int key)
{
	if (!p)
		return ;
	scale_property(a, &p->x, "kx", key, 0.01f);
	scale_property(a, &p->y, "ky", key, 0.01f);
	p->x = fabsf(p->x);
	p->y = fabsf(p->y);
	*p = v3_unitvec(*p);
}

void	mofify_float(t_app *a, float *p, int key)
{
	if (!p)
		return ;
	scale_property(a, p, "ky", key, 0.05f);
}
