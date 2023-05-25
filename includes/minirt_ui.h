/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_ui.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:36:13 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 17:49:03 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_UI_H
# define MINIRT_UI_H

#include "minirt_structs.h"

int	destroy_window(t_app *a);

int	mouse_movement_track(int x, int y, t_app *a);
int	mouse_on_click(int action, int x, int y, t_app *a);
int	mouse_on_release(int action, int x, int y, t_app *a);

int	keyboard_on_press(int key, t_app *a);
int	keyboard_on_release(int key, t_app *a);

int	assign_keybinds(t_app *a);

/* render_ui.c */

void	render_ui(t_app *a);

/* selection.c */

void	render_selection_ui(t_app *a, t_v2int pos);

/* make_selection.c */

int		screen_select(t_app *a);
void	modify_v3(t_v3 *p, int key);
void	mofify_float(float *p, int key, int type);
void	mofify_float_angle(float *p, int key);
void	modify_v3_unitvec(t_v3 *p, int key);
void	modify_v3_colour(t_v3 *p, int key);

/* ui_getters.c */
const char	*ret_p1_str(t_object *o);
const char	*ret_p2_str(t_object *o);
const char	*ret_p3_str(t_object *o);

#endif /* MINIRT_UI_H */
