/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_render.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:48:56 by znichola          #+#    #+#             */
/*   Updated: 2023/05/29 14:52:14 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_RENDER_H
# define MINIRT_RENDER_H

# include "minirt_structs.h"

/* put_pixel.c */

int			render_frame(t_app *a);

/* put_pixel.c */

void		my_mlx_pixel_put(t_img_data *img, int x, int y, int color);
void		fill_screen(t_img_data *img, int colour);

/* pix_shader.c */

t_v3		pix_shader(t_scene *s, t_object *me, t_intersection *i);

/* pix_shader2.c */

t_v3		get_light_diffuse(t_scene *s, int l_num, t_intersection *i);
t_v3		get_light_colour(t_scene *s, int l_num);

/* render_world.c */

int			render_world(t_app *a);
t_v3		draw_ray(t_app *a, t_ray ray);
t_ray		pixel_to_ray(t_app *a, int u, int v);
t_object	*find_poi(t_scene *s, t_v3 ray, t_v3 origin, t_intersection *i);
void		single_thread_render(t_app *a);

/* bump_map.c */

t_img_data	*get_obj_bmp(t_object *o);
t_v3		get_bmp_adjusted_normal(t_object *o, t_intersection *i);

/* texture.c */

void		load_texture(t_app	*app, t_img_data *texture);
t_v3		get_pix_from_texture(t_img_data *texture, t_v2f point);
int			get_pix_from_checkerboard(t_v2f point);
void		load_all_textures(t_app *a);

#endif /* MINIRT_RENDER_H */
