/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_primitives.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:41:17 by znichola          #+#    #+#             */
/*   Updated: 2023/05/21 10:15:35 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_PRIMITIVES_H
# define MINIRT_PRIMITIVES_H

#include "minirt_structs.h"

/* sphere.c */

t_v3	get_sp_emmision(t_object *me, t_intersection *i);
t_v3	get_sp_position(t_object *me);
float	get_sp_poi(t_object *me, t_v3 ray, t_v3 source, t_intersection *i);
t_v3	get_sp_poi_norm(t_object *obj, t_intersection *i);
t_v2f	spherical_map(t_sphere *sp, t_intersection *i);

/* cylinder.c */

t_v3	get_cy_emmision(t_object *me, t_intersection *i);
t_v3	get_cy_position(t_object *me);
float	get_cy_poi(t_object *me, t_v3 ray, t_v3 source, t_intersection *i);
t_v3	get_cy_poi_norm(t_object *obj, t_intersection *i);
t_v2f	cylindrical_map(t_cylinder *cy, t_intersection *in);

/* plane */

t_v3	get_pl_emmision(t_object *me, t_intersection *i);
t_v3	get_pl_position(t_object *me);
float	get_pl_poi(t_object *me, t_v3 ray, t_v3 source, t_intersection *i);
t_v3	get_pl_poi_norm(t_object *obj, t_intersection *i);
t_v2f	planar_map(t_plane *pl, t_intersection *i);

/* cone.c */

t_v3	get_co_emmision(t_object *me, t_intersection *i);
t_v3	get_co_position(t_object *me);
float	get_co_poi(t_object *me, t_v3 ray, t_v3 source, t_intersection *i);
t_v3	get_co_poi_norm(t_object *obj, t_intersection *i);
t_v2f	cone_map(t_cone *co, t_intersection *in);


#endif /* MINIRT_PRIMITIVES_H */
