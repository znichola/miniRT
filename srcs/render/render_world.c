/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:24:01 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/29 14:51:55 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	For each pixel in our image, compute it's color by computing
	a ray that goes	from the camera origin into the scene.
*/
int	render_world(t_app *a)
{
	if (!assign_keybinds(a))
		return (0);
	if (MRT_THREAD_COUNT > 1)
		multithread_render(a);
	else
		single_thread_render(a);
	render_ui(a);
	return (0);
}

/*
	Compute direction vector of the given pixel.
*/
t_ray	pixel_to_ray(t_app *a, int u, int v)
{
	t_ray	ray;
	t_v3	pix;
	float	world_x;
	float	world_y;

	world_x = a->s.camera.half_height - ((u + 0.5) * a->s.camera.pixel_size);
	world_y = a->s.camera.half_width - ((v + 0.5) * a->s.camera.pixel_size);
	pix = m4_x_v3(a->s.camera.inverse_transform, (t_v3){world_x, world_y, -1});
	ray.origin = m4_x_v3(a->s.camera.inverse_transform, origin());
	ray.direction = v3_unitvec(v3_subtract(pix, ray.origin));
	return (ray);
}

/*
	Compute the color of a ray.
*/
t_v3	draw_ray(t_app *a, t_ray ray)
{
	t_object		*closest;
	t_intersection	i;
	t_v3			col;

	i.is_marked = 0;
	closest = find_poi(&a->s, ray.direction, ray.origin, &i);
	if (i.is_marked == e_green)
		col = (t_v3){0.2, 1.0, 0.0};
	else if (i.is_marked == e_cyan)
		col = (t_v3){0, 0.9, 0.9};
	else if (i.is_marked == e_fuschia)
		col = (t_v3){1, 0, 0.2};
	else if (i.is_marked == e_indigo)
		col = (t_v3){0.5, 0, 1};
	else if (closest)
		col = pix_shader(&a->s, closest, &i);
	else
		col = a->s.ambiant.ambient;
	return (col);
}

/*
	Find closest object our ray intersects with.
	*poi is set to the point of intersection with that object.

	If the ray does not intersect with any object, NULL is returned.
*/
t_object	*find_poi(t_scene *s, t_v3 ray, t_v3 origin, t_intersection *i)
{
	t_list			*current;
	t_object		*closest;
	float			closest_dist;
	t_intersection	closest_i;
	float			dist;

	closest = NULL;
	closest_dist = FLT_MAX;
	current = s->objects_list;
	while (current)
	{
		dist = get_obj_poi(current->content, ray, origin, i);
		if (dist < closest_dist)
		{
			closest_i = *i;
			closest_dist = dist;
			closest = current->content;
		}
		current = current->next;
	}
	*i = closest_i;
	return (closest);
}

void	single_thread_render(t_app *a)
{
	int		u;
	int		v;
	t_ray	ray;
	t_v3	clr;

	u = 0;
	while (u < a->img.width)
	{
		v = 0;
		while (v < a->img.height)
		{
			ray = pixel_to_ray(a, u, v);
			clr = draw_ray(a, ray);
			my_mlx_pixel_put(&a->img, u, v, v3_to_col(clr));
			v++;
		}
		u++;
	}
	mlx_put_image_to_window(a->mlx_instance, a->window, a->img.img, 0, 0);
}
