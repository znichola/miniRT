/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:02:04 by znichola          #+#    #+#             */
/*   Updated: 2023/05/18 11:52:32 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		ui_put_string(t_app *a, char *s, t_v2int *p);
static void		ui_put_v3(t_app *a, t_v2int *p, const char *s, t_v3 v);
static const char	*ret_p1_str(t_object *o);
static const char	*ret_p2_str(t_object *o);
static const char	*ret_p3_str(t_object *o);

void	render_selection_ui(t_app *a, t_v2int pos)
{
	char	txt[100];

	ui_put_v3(a, &pos, "camera pos:",
		a->s.camera.position);
	ui_put_v3(a, &pos, "camera dir:",
		a->s.camera.orientation);
	sprintf(txt, "camera fov: %f", a->s.camera.fov);
	ui_put_string(a, txt, &pos);

	pos.y += 10;
	sprintf(txt, "%s[%p]", ret_obj_string(a->selected), a->selected);
	ui_put_string(a, txt, &pos);
	ui_put_v3(a, &pos, "[g] pos", get_obj_pos(a->selected));
	ui_put_v3(a, &pos, "[t] dir", get_obj_dir(a->selected));
	ui_put_v3(a, &pos, "[y] col", get_obj_col(a->selected));
	sprintf(txt, "[b] %s(%.2f)", ret_p1_str(a->selected), get_obj_p1(a->selected));
	ui_put_string(a, txt, &pos);
	sprintf(txt, "[h] %s(%.2f)", ret_p2_str(a->selected), get_obj_p2(a->selected));
	ui_put_string(a, txt, &pos);
	sprintf(txt, "[n] %s(%.2f)", ret_p3_str(a->selected), get_obj_p3(a->selected));
	ui_put_string(a, txt, &pos);
}

static void	ui_put_string(t_app *a, char *s, t_v2int *p)
{
	mlx_string_put(a->mlx_instance, a->window, p->x, p->y, MRT_WHITE, s);
	p->y += 12;
}

static void	ui_put_v3(t_app *a, t_v2int *p, const char *s, t_v3 v)
{
	char	txt[100];

	sprintf(txt, "%s(%.2f, %.2f, %.2f)", s, v.x, v.y, v.z);
	mlx_string_put(a->mlx_instance, a->window, p->x, p->y, MRT_WHITE, txt);
	p->y += 12;
}

static const char	*ret_p1_str(t_object *o)
{
	const char	*s[6] = {"ratio", "fov", "ratio", "radius", "none", "hight_start"};
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
	return (s[4]);
}

static const char	*ret_p2_str(t_object *o)
{
	const char	*s[2] = {"height", "none"};
	if (o->type == e_cylinder)
		return (s[0]);
	if (o->type == e_cone)
		return (s[0]);
	return (s[1]);
}

static const char	*ret_p3_str(t_object *o)
{
	const char	*s[2] = {"angle", "none"};
	if (o->type == e_cone)
		return (s[0]);
	return (s[1]);
}
