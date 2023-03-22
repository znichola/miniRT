/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_render.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:48:56 by znichola          #+#    #+#             */
/*   Updated: 2023/03/22 18:40:44 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_RENDER_H
# define MINIRT_RENDER_H

#include "minirt_structs.h"

int		render_frame(t_app *a);
void	my_mlx_pixel_put(t_img_data *img, int x, int y, int color);
void	wrapper_pixel_put(t_img_data *img, int x, int y, int colour);

void	put_circle_fast(t_img_data *img, int r, t_v2int center, int colour);
void	fill_screen(t_img_data *img, int colour);

void	render_sphere(t_app *a);
void	resulting_colour(t_app *a, t_v2int pix, t_v3 intersection, t_v3 center);


int		calculate_px_colour(t_app *a, float angle, int	l_colour, float l_brightness , int obj_colour);

t_v3	reflection(t_v3 incident, t_v3 surface_normal);


// trgp_colour.c
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

int		colour_lerp(float min, float max, float point);
int		colour_pallet_lerp(float min, float max, float point, t_v2int pallet);
int		colour_pallet_add(int x, int y);
int		colour_pallet_multiply(int x, int y);
int		colour_brightness_multi(int x, float b);

int		moon_texture(t_app *app, int x, int y);
int		earth_texture(t_app *app, int x, int y);
int		earth_bmp_texture(t_app *app, int x, int y);
int		earth_nightlight_texture(t_app *app, int x, int y);

/* multithread.c */

void	*thread_routine(void *info_struct);
void	start_threads(t_app *a);
void	get_or_release_locks(t_app *a, int action);

/* render colour */
int		render_colour_frame(t_app *a);
int		v3_to_col(t_v3 v);
t_v3	col_add(t_v3 a, t_v3 b);
t_v3	col_multi(t_v3 a, t_v3 b);


int	render_world(t_app *a);

#endif /* MINIRT_RENDER_H */
