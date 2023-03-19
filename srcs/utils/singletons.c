/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:28:31 by znichola          #+#    #+#             */
/*   Updated: 2023/03/19 11:45:53 by znichola         ###   ########.fr       */
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
	t_v2int			diff;

	if (key < 0 || key > MOUSE_KEY_COUNT)
		;
	else if (a->mouse_key_held[key])
	{
		diff.x = a->mouse_pos_old.x - a->mouse_pos.x;
		diff.y = a->mouse_pos_old.y - a->mouse_pos.y;
		// printf("old(%d, %d) current(%d, %d) diff(%d, %d)\n", a->mouse_pos_old.x, a->mouse_pos_old.y, a->mouse_pos.x, a->mouse_pos.y, a->mouse_pos_old.x - a->mouse_pos.x, a->mouse_pos_old.y - a->mouse_pos.y);
		return (diff);
	}
	return ((t_v2int){0, 0});
}

t_v2int	get_keyboard_diff(t_app *a, int key)
{
	t_v2int			diff;

	if (key < 0 || key > KEYBOARD_KEY_COUNT)
		;
	else if (a->keyboard_held[key])
	{
		printf("there %d\n", key);
		diff.x = a->mouse_pos_old.x - a->mouse_pos.x;
		diff.y = a->mouse_pos_old.y - a->mouse_pos.y;
		return (diff);
	}
	return ((t_v2int){0, 0});
}

/*
	ctrl [k/m][x/y]
	use ctrl to control the key you wish to bind, keyboard or mouse
	and the change in which mouse axis you want to map to.
*/
int	scale_property(t_app *a, float *property, char *ctrl, int key, float factor)
{
	t_v2int	diff;

	if (ctrl[0] == 'm')
		diff = get_mouse_diff(a, key);
	else if (ctrl[0] == 'k')
		diff = get_keyboard_diff(a, key);
	if (ctrl[1] == 'x')
		*property += diff.x * factor;
	else if (ctrl[1] == 'y')
		*property += diff.y * factor;
	else
		return (0);
	// printf("old(%d, %d) current(%d, %d) diff(%d, %d)\n", a->mouse_pos_old.x, a->mouse_pos_old.y, a->mouse_pos.x, a->mouse_pos.y, a->mouse_pos_old.x - a->mouse_pos.x, a->mouse_pos_old.y - a->mouse_pos.y);
	// printf("getting diff %s %d, %d\n", ctrl, diff.x, diff.y);
	return (1);
}
