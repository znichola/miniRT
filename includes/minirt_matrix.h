/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_matrix.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:50:21 by znichola          #+#    #+#             */
/*   Updated: 2023/05/19 22:22:48 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MATRIX_H
# define MINIRT_MATRIX_H

# include "minirt_structs.h"

/* view_transformation.c */

t_m4	view_transform(t_v3 from, t_v3 to, t_v3 up);

/* matrix.c */

t_m4	m4_x_m4(t_m4 a, t_m4 b);
t_m4	translation(float x, float y, float z);
int		m4_is_invertable(t_t4 m);
t_m4	m4_inverse(t_m4 m);

/* t3_determinant.c */

float	t3_determinant(t_t3 t);
float	t3_cofactor(t_t3 t, int i, int j);
float	t3_minor(t_t3 t, float i, float j);
t_t2	t3_submatrix(t_t3 t, int remove_i, int remove_j);

/* t4_determinant.c */

float	t4_determinant(t_t4 t);
float	t4_cofactor(t_t4 t, int i, int j);
float	t4_minor(t_t4 t, float i, float j);
t_t3	t4_submatrix(t_t4 t, int remove_i, int remove_j);

/* helper.c */

float	t2_determinant(t_t2 t);
t_t4	m4_to_t(t_m4 *m);
t_m4	t4_to_m(t_t4 t);


#endif /* MINIRT_MATRIX_H */
