/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:46:11 by znichola          #+#    #+#             */
/*   Updated: 2023/03/23 01:05:12 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_UTILS_H
# define MINIRT_UTILS_H

#include "minirt_structs.h"

void	print_v3(char *name, t_v3 *v);
int		imin(int a, int b);
int		imax(int a, int b);

/* sigletons.c */
int		getset_settings(int settings_mask);
t_v2int	get_mouse_diff(t_app *a, int key);
int		scale_property(t_app *app, float *property, char *ctrl, int key, float factor);
float	get_ratio(t_app *a, char action, int px);


/* debug prints */

void	print_image(t_app *a);


#endif /* MINIRT_UTILS_H */
