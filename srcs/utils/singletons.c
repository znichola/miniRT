/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:28:31 by znichola          #+#    #+#             */
/*   Updated: 2023/03/18 11:52:33 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	mask used to store setting to setup the app.
*/
int	getset_settings(int settings_mask)
{
	static int	set = 1;
	static int	mask = 0U;

	if (set)
	{
		mask = settings_mask;
		set = 0;
	}
	return (settings_mask & mask);
}

t_v2int	get_mouse_diff(t_app *a, int key)
{
	static t_v2int	old_pos[MOUSE_KEY_COUNT];
	t_v2int			diff;

	if (key < 0 || key > MOUSE_KEY_COUNT)
		;
	else if (a->mouse_key_click[key])
	{
		old_pos[key] = a->mouse_pos;
	}
	else if (a->mouse_key_held[key])
	{
		float	*scale_a = &a->l_origin.y;
		float	*scale_b = &a->l_origin.x;
		diff.x = old_pos[key].y - a->mouse_pos.y;
		diff.y = old_pos[key].x - a->mouse_pos.x;
		old_pos[key] = a->mouse_pos;
		return (diff);
	}
	return ((t_v2int){0, 0});
}

int	scale_property(t_app *app, float *property, char mouse_axis, int key, int factor)
{
	t_v2int	diff;

	diff = get_mouse_diff(app, key);

	if (mouse_axis == 'x')
		*property += diff.x * factor;
	else if (mouse_axis == 'y')
		*property += diff.y * factor;
}
