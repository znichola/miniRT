/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_maths.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:48:23 by znichola          #+#    #+#             */
/*   Updated: 2023/03/13 18:53:30 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MATHS_H
# define MINIRT_MATHS_H

# include "minirt_structs.h"

float	v3_mag(t_v3 v);
t_v3	v3_norm(t_v3 v);
t_v3	v3_perp(t_v3 v);
float	v3_dot(t_v3 a, t_v3 b);
float	v3_cross(t_v3 a, t_v3 b);
t_v3	v3_vadd(t_v3 a, t_v3 b);
t_v3	v3_subtract(t_v3 a, t_v3 b);
t_v3	v3_multiply(t_v3 v, float s);
t_v3	v3_divide(t_v3 v, float s);


#endif /* MINIRT_VECTOR_H */
