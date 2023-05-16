/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:24:01 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/16 16:14:20 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	single_thread_render(t_app *a);

/*
	For each pixel in our image, compute it's color by computing a ray that goes
	from the camera origin into the scene.
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
t_v3	pixel_to_ray(t_app *a, int u, int v)
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

/*
	Compute the color of a ray.
*/
t_v3	draw_ray(t_app *a, t_v3 ray)
{
	t_object		*closest;
	t_intersection	i;
	t_v3			col;

	i.is_marked = 0;
	closest = find_poi(&a->s, ray, a->s.camera.position, &i);
	if (i.is_marked == 42)
		col = (t_v3){0.2,1.0,0.0};
	else if (i.is_marked == 43)
		col = (t_v3){0, 0.9, 0.9};
	else if (i.is_marked == 44)
		col = (t_v3){1,0,0.2};
	else if (i.is_marked == 45)
		col = (t_v3){0.5, 0, 1};
	else if (closest)
		col = pix_shader(&a->s, closest, &i);
	else
		col = (t_v3){0.2,0.2,0.2};
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

static void	single_thread_render(t_app *a)
{
	int		u;
	int		v;
	t_v3	ray;
	t_v3	clr;

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
	mlx_put_image_to_window(a->mlx_instance, a->window, a->img.img, 0, 0);
}
