/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_render.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:48:56 by znichola          #+#    #+#             */
/*   Updated: 2023/05/01 17:55:30 by skoulen          ###   ########.fr       */
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

void	put_line(t_img_data *img, t_v2int p1, t_v2int p2);
t_v3	finite_diff(t_app *a, float tu, float tv);

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

/* render_world.c */

int		render_world(t_app *a);

/* pix_shader.c */

t_v3	pix_shader(t_scene *s, t_object *me, t_v3 poi);

#endif /* MINIRT_RENDER_H */
