/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:46:11 by znichola          #+#    #+#             */
/*   Updated: 2023/05/01 17:58:34 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_UTILS_H
# define MINIRT_UTILS_H

#include "minirt_structs.h"

/* singletons.c */

int		getset_settings(int settings_mask);
t_v2int	get_mouse_diff(t_app *a, int key);
int		scale_property(t_app *app, float *property, char *ctrl, int key, float factor);
float	get_ratio(t_app *a, char action, int px);
int		get_world_to_pix_ratio(t_app *a, char action, float wrld);
t_app	*getset_app(t_app *a);


/* debug_prints */

void	print_v3(char *name, t_v3 v);
int		imin(int a, int b);
int		imax(int a, int b);
void	print_image(t_app *a);


/* trgb.c */

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

#endif /* MINIRT_UTILS_H */
