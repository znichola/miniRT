/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_primitives.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:41:17 by znichola          #+#    #+#             */
/*   Updated: 2023/03/22 23:17:25 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_PRIMITIVES_H
# define MINIRT_PRIMITIVES_H

#include "minirt_structs.h"

/* sphere.c */

t_v3	get_sp_emmision(t_object *me, t_v3 poi);
t_v3	get_sp_position(t_object *me);
float	get_sp_poi(t_object *me, t_v3 ray, t_v3 source, t_v3 *poi);

/* cylinder.c */

t_v3	get_cy_emmision(t_object *me, t_v3 poi);
t_v3	get_cy_position(t_object *me);
float	get_cy_poi(t_object *me, t_v3 ray, t_v3 source, t_v3 *poi);

/* plane */

t_v3	get_pl_emmision(t_object *me, t_v3 poi);
t_v3	get_pl_position(t_object *me);
float	get_pl_poi(t_object *me, t_v3 ray, t_v3 source, t_v3 *poi);

#endif /* MINIRT_PRIMITIVES_H */
