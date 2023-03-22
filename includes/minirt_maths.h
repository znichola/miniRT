/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_maths.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:48:23 by znichola          #+#    #+#             */
/*   Updated: 2023/03/22 10:51:21 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MATHS_H
# define MINIRT_MATHS_H

# include "minirt_structs.h"

float		v3_mag(t_v3 v);
t_v3		v3_unitvec(t_v3 v);
t_v3		v3_perp(t_v3 v);
float		v3_dot(t_v3 a, t_v3 b);
t_v3		v3_cross(t_v3 a, t_v3 b);
t_v3		v3_add(t_v3 a, t_v3 b);
t_v3		v3_subtract(t_v3 a, t_v3 b);
t_v3		v3_multiply(t_v3 v, float s);
t_v3		v3_divide(t_v3 v, float s);

t_v3 		v3_multiply_matrix(t_v3 i, t_mat4x4 t);
t_mat4x4	direction_mat(t_v3 dir);

int			poi_sphere(t_sphere *me, t_v3 ray, t_v3 source, t_v3 *poi);

#endif /* MINIRT_VECTOR_H */
