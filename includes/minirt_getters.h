/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_getters.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:27:27 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/12 13:04:53 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_GETTERS_H
# define MINIRT_GETTERS_H

t_light	*get_light(t_scene *s, int num);
t_v3	get_obj_emmision(t_object *obj, t_intersection *i);
t_v3	get_obj_pos(t_object *obj);
float	get_obj_poi(t_object *obj, t_v3 ray, t_v3 source, t_intersection *i);
t_v3	get_poi_norm(t_object* obj, t_intersection *i);

t_v3	get_obj_col(t_object *o);
t_v3	get_obj_dir(t_object *o);
float	get_obj_p1(t_object *o);
float	get_obj_p2(t_object *o);
float	get_obj_p3(t_object *o);

t_v3	*ref_obj_pos(t_object *o);
t_v3	*ref_obj_col(t_object *o);
t_v3	*ref_obj_dir(t_object *o);
float	*ref_obj_p1(t_object *o);
float	*ref_obj_p2(t_object *o);
float	*ref_obj_p3(t_object *o);

#endif /* MINIRT_GETTERS_H */
