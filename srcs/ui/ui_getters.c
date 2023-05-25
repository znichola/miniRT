/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_getters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:24:03 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 13:24:27 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

const char	*ret_p1_str(t_object *o)
{
	static char	*s[6] = {
		"ratio", "fov", "ratio", "radius", "none", "hight_start"};

	if (o->type == e_ambiant)
		return (s[0]);
	else if (o->type == e_sphere)
		return (s[3]);
	else if (o->type == e_cylinder)
		return (s[3]);
	else if (o->type == e_light)
		return (s[2]);
	else if (o->type == e_cone)
		return (s[5]);
	else if (o->type == e_camera)
		return (s[1]);
	return (s[4]);
}

const char	*ret_p2_str(t_object *o)
{
	static char	*s[2] = {"height", "none"};

	if (o->type == e_cylinder)
		return (s[0]);
	if (o->type == e_cone)
		return (s[0]);
	return (s[1]);
}

const char	*ret_p3_str(t_object *o)
{
	static char	*s[2] = {"angle", "none"};

	if (o->type == e_cone)
		return (s[0]);
	return (s[1]);
}
