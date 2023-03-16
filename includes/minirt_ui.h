/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_ui.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:36:13 by znichola          #+#    #+#             */
/*   Updated: 2023/03/13 16:56:20 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_UI_H
# define MINIRT_UI_H

#include "minirt_structs.h"

int	destroy_window(t_app *a);
int	mouse_movement_track(int x, int y, t_app *a);
int	mouse_on_click(int action, int x, int y, t_app *a);
int	mouse_on_release(int action, int x, int y, t_app *a);
int	keyboard_press(int key, t_app *a);

#endif /* MINIRT_UI_H */
