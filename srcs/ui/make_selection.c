/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_selection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:13:28 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 11:26:25 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	scroll_value(t_app *a, float *p, float inc);

int	screen_select(t_app *a)
{
	t_ray			ray;
	t_object		*obj;
	t_intersection	i;

	i.is_marked = 0;
	ray = pixel_to_ray(a, a->mouse_pos.x, a->mouse_pos.y);
	obj = find_poi(&a->s, ray.direction, ray.origin, &i);
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
	scale_property(a, &p->y, "ky-", key, 0.05f);
	if (a->keyboard_held[key])
		scroll_value(a, &p->z, 5.0f);
}

void	modify_v3_unitvec(t_app *a, t_v3 *p, int key)
{
	if (!p)
		return ;
	scale_property(a, &p->x, "kx", key, 0.001f);
	scale_property(a, &p->y, "ky-", key, 0.001f);
	if (a->keyboard_held[key])
		scroll_value(a, &p->z, .1f);
	*p = v3_unitvec(*p);
}

void	modify_v3_colour(t_app *a, t_v3 *p, int key)
{
	if (!p)
		return ;
	scale_property(a, &p->x, "kx", key, 0.01f);
	scale_property(a, &p->y, "ky-", key, 0.01f);
	if (a->keyboard_held[key])
		scroll_value(a, &p->z, .1f);
	p->x = fabsf(p->x);
	p->y = fabsf(p->y);
	p->z = fabsf(p->z);
	// *p = v3_unitvec(*p);
}

void	mofify_float(t_app *a, float *p, int key, int type)
{
	float	incr;

	if (type == e_light)
		incr = 0.005f;
	else
		incr = 0.05f;
	if (!p)
		return ;
	scale_property(a, p, "ky-", key, incr);
	if (*p < FLT_EPSILON)
		*p = 0.0f;
	if (type == e_light && (*p - 1.0f) > FLT_EPSILON)
		*p = 1.0f;
}

void	mofify_float_angle(t_app *a, float *p, int key)
{
	if (!p)
		return ;
	scale_property(a, p, "ky-", key, 0.05f);
	if (*p < 0.1f)
		*p = 0.1f;
	else if (*p > M_PI_2)
		*p = M_PI_2;
}

static void	scroll_value(t_app *a, float *p, float inc)
{
	if (a->mouse_key_click[e_mouse_scroll_up])
		*p += inc;
	if (a->mouse_key_click[e_mouse_scroll_down])
		*p -= inc;
}
