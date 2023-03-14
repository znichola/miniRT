/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_render.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:48:56 by znichola          #+#    #+#             */
/*   Updated: 2023/03/14 00:48:31 by znichola         ###   ########.fr       */
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
void	calculate_shadow(t_app *a, t_v2int pix, t_v3 intersection, t_v3 center);
int		colour_lerp(float min, float max, float point);

// trgp_colour.c
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);


#endif /* MINIRT_RENDER_H */
