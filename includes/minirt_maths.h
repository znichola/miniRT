/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_maths.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:48:23 by znichola          #+#    #+#             */
/*   Updated: 2023/03/22 23:17:40 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MATHS_H
# define MINIRT_MATHS_H

# include "minirt_structs.h"

# define V_I (t_v3){1.0, 0.0, 0.0}
# define V_J (t_v3){0.0, 1.0, 0.0}
# define V_K (t_v3){0.0, 0.0, 1.0}

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

float		poi_sphere(t_sphere *me, t_v3 ray, t_v3 source, t_v3 *poi);

#endif /* MINIRT_VECTOR_H */
