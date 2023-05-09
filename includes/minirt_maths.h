/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_maths.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:48:23 by znichola          #+#    #+#             */
/*   Updated: 2023/05/09 10:56:46 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MATHS_H
# define MINIRT_MATHS_H

# include "minirt_structs.h"

# define V_I (t_v3){1.0, 0.0, 0.0}
# define V_J (t_v3){0.0, 1.0, 0.0}
# define V_K (t_v3){0.0, 0.0, 1.0}

/* vector.c */

float		v3_mag(t_v3 v);
t_v3		v3_unitvec(t_v3 v);
t_v3		v3_perp(t_v3 v);
float		v3_dot(t_v3 a, t_v3 b);
t_v3		v3_cross(t_v3 a, t_v3 b);
t_v3		v3_add(t_v3 a, t_v3 b);
t_v3		v3_subtract(t_v3 a, t_v3 b);
t_v3		v3_multiply(t_v3 v, float s);
t_v3		v3_divide(t_v3 v, float s);

/* matrix.c */

t_v3 		v3_multiply_matrix(t_v3 i, t_mat4x4 t);
t_mat4x4	direction_mat(t_v3 dir);

/* colour.c */

int			v3_to_col(t_v3 v);
t_v3		col_add(t_v3 a, t_v3 b);
t_v3		col_multi(t_v3 a, t_v3 b);
t_v3		col_scale(t_v3 a, float s);
t_v2f		v2sub(t_v2f a, t_v2f b);
t_v2f		v2add(t_v2f a, t_v2f b);
float		v2mag(t_v2f v);
t_v2f		bound(t_v2f v, float min, float max);
int			left_ofline(t_v2f s1, t_v2f s2, t_v2f cur);

/* poi_sphere.c */
float		poi_sphere(t_sphere *me, t_v3 ray, t_v3 source, t_v3 *poi);

/* poi_plane.c */
float		poi_plane(t_plane *me, t_v3 ray, t_v3 source, t_v3 *poi);

/* poi_cylinder.c */
float		poi_cylinder(t_cylinder *me, t_v3 ray, t_v3 source, t_v3 *poi);

#endif /* MINIRT_VECTOR_H */
