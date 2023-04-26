/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:24:01 by skoulen           #+#    #+#             */
/*   Updated: 2023/04/25 15:04:22 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <float.h>

static t_v3	pixel_to_ray(t_app *a, int u, int v);
static t_v3	draw_ray(t_app *a, t_v3 ray);

t_v3	get_obj_emmision(t_object *obj, t_v3 poi);
t_v3	get_obj_pos(t_object *obj);
float	get_obj_lightfactor(t_scene *s, t_object *me, t_v3 poi);

t_light		*get_light(t_scene *s, int num);

t_v2int	world_to_screen(t_app *a, t_v3 world);

int	render_world(t_app *a)
{
	int		u;
	int		v;
	t_v3	ray;
	t_v3	clr;

	if (!assign_keybinds(a))
		return (0);

	u = 0;
	while (u < a->img.width)
	{
		v = 0;
		while (v < a->img.height)
		{
			ray = pixel_to_ray(a, u, v);
			clr = draw_ray(a, ray);
			wrapper_pixel_put(&a->img, u, v, v3_to_col(clr));
			v++;
		}
		u++;
	}

	// this function is broken only seems to track the 0,0,0 position and not the object's pos
	// put_circle_fast(&a->img, 4, world_to_screen(a, get_obj_pos(a->s.objects_list->content)), MRT_PINK);

	// put_line(&a->img,	world_to_screen(a, ORIGIN),
	// 					world_to_screen(a, v3_multiply(get_obj_pos(a->s.objects_list->content), -1000)));
	// put_line(&a->img,	world_to_screen(a, get_light(&a->s, 0)->position),
	// 					world_to_screen(a, v3_multiply(get_light(&a->s, 0)->position, -1000)));
	mlx_put_image_to_window(a->mlx_instance, a->window, a->img.img, 0, 0);
	render_ui(a);
	return (0);
}

// https://math.stackexchange.com/questions/2305792/3d-projection-on-a-2d-plane-weak-maths-ressources

static t_v3	pixel_to_ray(t_app *a, int u, int v)
{
	t_v3	ray;

	/*
		create a ray from the origin through the pixel in question. Assuming
		the camera is fixed at (0, 0, 0) and looking at (0,0,1)
	*/
	ray = (t_v3){get_ratio(a, 'w', u), get_ratio(a, 'h', v), 1};

	/*
		now we should have a transformation matrix that translates this
		calculated ray to the camera position, then orients it.
	*/

	/*
		translate the pixel/ray to the correct posisiton.
	*/
	ray = v3_add(ray, a->s.camera.position);

	return (ray);
}

static t_v3	draw_ray(t_app *a, t_v3 ray)
{
	//given a ray, compute the color of the associated pixel?
	t_object	*closest;
	t_v3		poi;
	t_v3		col;

	closest = find_poi(&a->s, ray, a->s.camera.position, &poi);
	if (closest)
		// col = closest->object.sp.colour;
		col = pix_shader(&a->s, closest, a->s.camera.position, poi);
	else
		// col = v3_multiply(a->s.ambiant.colour, a->s.ambiant.ratio);
		col = (t_v3){0.2,0.2,0.2};
	return (col);
}

/*
	poi means: "point of intersection"
*/
t_object	*find_poi(t_scene *s, t_v3 ray, t_v3 origin, t_v3 *poi)
{
	t_list		*current;
	t_object	*closest;
	float		closest_dist;
	t_v3		closest_poi;
	float		dist;

	closest = NULL;
	closest_dist = FLT_MAX;
	current = s->objects_list;
	while (current)
	{
		dist = get_obj_poi(current->content, ray, origin, poi);
		if (dist < closest_dist)
		{
			closest_poi = *poi;
			closest_dist = dist;
			closest = current->content;
		}
		current = current->next;
	}
	// printf("%.2f ", closest_dist); /*for debug writing into a file*/
	*poi = closest_poi;
	return (closest);
}

t_v2int	world_to_screen(t_app *a, t_v3 world)
{
	t_v3	p0 = world;
	t_v3	p1 = v3_add(a->s.camera.position, a->s.camera.orientation);

	t_v3	pco = p1;
	t_v3	pno = a->s.camera.orientation;

	t_v3	u;
	float	dot;

	u = v3_subtract(p1, p0);
	dot = v3_dot(pno, u);

	if (fabsf(dot) > FLT_EPSILON)
	{
		t_v3	w = v3_subtract(p0, pco);
		float	fac = - v3_dot(pno, w) / dot;
		u = v3_multiply(u, fac);
		t_v3	ans = v3_add(p0, u);
		return ((t_v2int){get_world_to_pix_ratio(a, 'w', -ans.x),
						get_world_to_pix_ratio(a, 'h', -ans.y)});
	}
	return ((t_v2int){0, 0});
}
