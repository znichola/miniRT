/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:53:08 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 13:17:19 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	keyboard_on_press(int key, t_app *a)
{
	if (key == e_key_esc)
		destroy_window(a);
	if (key >= 0 && key < KEYBOARD_KEY_COUNT)
	{
		a->keyboard_press[key] = 1;
		a->keyboard_held[key] = 1;
	}
	return (0);
}

int	keyboard_on_release(int key, t_app *a)
{
	if (key >= 0 && key < KEYBOARD_KEY_COUNT)
	{
		a->keyboard_release[key] = 1;
		a->keyboard_held[key] = 0;
	}
	return (0);
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
