/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:28:31 by znichola          #+#    #+#             */
/*   Updated: 2023/03/28 12:17:30 by znichola         ###   ########.fr       */
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
		// printf("there %d\n", key);
		diff.x = a->mouse_pos.x - a->mouse_pos_old.x;
		diff.y = a->mouse_pos.y - a->mouse_pos_old.y;
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
	float	dir;

	if (ctrl[2] == '-')
		dir = -1.0;
	else
		dir = 1.0;
	if (ctrl[0] == 'm')
		diff = get_mouse_diff(a, key);
	else if (ctrl[0] == 'k')
		diff = get_keyboard_diff(a, key);
	if (ctrl[1] == 'x')
		*property = *property + (dir * (float)diff.x) * factor;
	else if (ctrl[1] == 'y')
		*property = *property + (dir * (float)diff.y) * factor;
	else
		return (0);
	// printf("old(%d, %d) current(%d, %d) diff(%d, %d)\n", a->mouse_pos_old.x, a->mouse_pos_old.y, a->mouse_pos.x, a->mouse_pos.y, a->mouse_pos_old.x - a->mouse_pos.x, a->mouse_pos_old.y - a->mouse_pos.y);
	// printf("getting diff %s %d, %d\n", ctrl, diff.x, diff.y);
	// printf("(%.1f)\n", *property * (180 / M_PI ));
	// printf("(%.1f)\n", *property);
	return (1);
}

/*
	used to get the aspect ratio converted to wold space
	be carefull it's got statics so threads amke sure it's not changing.
*/
float	get_ratio(t_app *a, char action, int px)
{
	static t_v2int	extents;
	static t_v3		cam_ratio;
	static t_v3		offset;

	if (a->img.height != extents.x
		|| a->img.width != extents.y
		|| a->s.camera.fov != cam_ratio.z)
	{
		extents.x = a->img.height;
		extents.y = a->img.width;
		cam_ratio.x = tanf(a->s.camera.fov / 2);
		cam_ratio.y = tanf((a->s.camera.fov / 2) * (extents.x / extents.y));
		offset.x = cam_ratio.x / 2;
		offset.y = cam_ratio.y / 2;
	}
	if (action == 'w')
		return (cam_ratio.x * ((double)px / extents.x) - offset.x);
	if (action == 'h')
		return (cam_ratio.y * ((double)px / extents.y) - offset.y);
	return (0.0);
}

/*
	used to get the aspect ratio converted to wold space
	be carefull it's got statics so threads amke sure it's not changing.
*/
int	get_world_to_pix_ratio(t_app *a, char action, float wrld)
{
	static t_v2int	extents;
	static t_v3		cam_ratio;
	static t_v3		offset;

	if (a->img.height != extents.x
		|| a->img.width != extents.y
		|| a->s.camera.fov != cam_ratio.z)
	{
		extents.x = a->img.height;
		extents.y = a->img.width;
		cam_ratio.x = tanf(a->s.camera.fov / 2);
		cam_ratio.y = tanf((a->s.camera.fov / 2) * (extents.x / extents.y));
		offset.x = cam_ratio.x / 2;
		offset.y = cam_ratio.y / 2;
	}
	if (action == 'w')
		return ((wrld + offset.x) / cam_ratio.x * (float)extents.x);
	if (action == 'h')
		return ((wrld + offset.y) / cam_ratio.y * (float)extents.y);
	return (0);
}

t_app	*getset_app(t_app *a)
{
	static t_app	*app;

	if (a)
		app = a;
	return (app);
}
