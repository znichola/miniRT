/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:02:04 by znichola          #+#    #+#             */
/*   Updated: 2023/05/29 14:02:18 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void			ui_put_string(t_app *a, char *s, t_v2int *p);
static void			ui_put_v3(t_app *a, t_v2int *p, const char *s, t_v3 v);

void	render_selection_ui(t_app *a, t_v2int pos)
{
	char	txt[100];

	if (a->selected->type == e_camera)
	{
		ui_put_v3(a, &pos, "camera pos:", a->s.camera.position);
		ui_put_v3(a, &pos, "camera dir:", a->s.camera.orientation);
		sprintf(txt, "camera fov: %.1f", a->s.camera.fov * 180.0f / M_PI_2);
		ui_put_string(a, txt, &pos);
		return ;
	}
	sprintf(txt, "%s[%p]", ret_obj_string(a->selected), a->selected);
	ui_put_string(a, txt, &pos);
	ui_put_v3(a, &pos, "[g] pos", get_obj_pos(a->selected));
	ui_put_v3(a, &pos, "[t] dir", get_obj_dir(a->selected));
	ui_put_v3(a, &pos, "[y] col", get_obj_col(a->selected));
	sprintf(txt, "[b] %s(%.2f)", ret_p1_str(a->selected),
		get_obj_p1(a->selected));
	ui_put_string(a, txt, &pos);
	sprintf(txt, "[h] %s(%.2f)", ret_p2_str(a->selected),
		get_obj_p2(a->selected));
	ui_put_string(a, txt, &pos);
	sprintf(txt, "[n] %s(%.2f)", ret_p3_str(a->selected),
		get_obj_p3(a->selected));
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
