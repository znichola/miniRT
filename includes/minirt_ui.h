/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_ui.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:36:13 by znichola          #+#    #+#             */
/*   Updated: 2023/05/11 22:25:44 by znichola         ###   ########.fr       */
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
void	modify_v3(t_app *a, t_v3 *p, int key);
void	mofify_float(t_app *a, float *p, int key);
void	modify_v3_unitvec(t_app *a, t_v3 *p, int key);
void	modify_v3_colour(t_app *a, t_v3 *p, int key);


#endif /* MINIRT_UI_H */
