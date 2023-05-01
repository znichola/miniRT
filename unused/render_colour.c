/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_colour.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:16:08 by znichola          #+#    #+#             */
/*   Updated: 2023/05/01 17:48:45 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_v2f	bound(t_v2f v, float min, float max);
static int		left_ofline(t_v2f s1, t_v2f s2, t_v2f cur);

int	render_colour_frame(t_app *a)
{
	int		u;
	int		v;
	t_v2int	extensts = (t_v2int){800, 800};

	static t_v2f	s1 = {0.5, 0.25};
	static t_v2f	s2 = {0.25, 0.75};
	static t_v2f	s3 = {0.75, 0.75};

	t_v2f	cur = {0};

	t_v3	c1 = {0};
	t_v3	c2 = {0};
	t_v3	c3 = {0};

	t_v3	col = {0};


	scale_property(a, &s1.x, "mx-", e_mouse_right, 0.001);
	scale_property(a, &s1.y, "my-", e_mouse_right, 0.001);
	scale_property(a, &s3.x, "mx-", e_mouse_middle, 0.001);
	scale_property(a, &s3.y, "my-", e_mouse_middle, 0.001);
	scale_property(a, &s2.x, "mx-", e_mouse_left, 0.001);
	scale_property(a, &s2.y, "my-", e_mouse_left, 0.001);

	float	m1 = fmaxf(v2mag(v2sub(s1, s2)), v2mag(v2sub(s1, s3)));
	float	m2 = fmaxf(v2mag(v2sub(s2, s1)), v2mag(v2sub(s2, s3)));
	float	m3 = fmaxf(v2mag(v2sub(s3, s1)), v2mag(v2sub(s3, s2)));

	v = -1;
	while (++v < a->img.height)
	{
		u = -1;
		while (++u < a->img.width)
		{
			/* convert from pixel to world coords*/
			cur = (t_v2f){(float)u / extensts.x, (float)v / extensts.y};

			/* colour addition */
			c1 = (t_v3){v2mag(v2sub(s1, cur)) / m1, 0, 0};
			c2 = (t_v3){0, v2mag(v2sub(s2, cur)) / m2, 0};
			c3 = (t_v3){0, 0, v2mag(v2sub(s3, cur)) / m3};

			col = col_add(col_add(c1, c2), c3);

			/* colour multiplication */
			// c1 = (t_v3){v2mag(v2sub(s1, cur)), 1, 1};
			// c2 = (t_v3){1, v2mag(v2sub(s2, cur)), 1};
			// c3 = (t_v3){1, 1, v2mag(v2sub(s3, cur))};

			// col = col_multi(col_multi(c1, c2), c3);

			/* put image to screen */
			// printf("s1 sub s2 (%.3f, %.3f)\n", v2sub(s1, s2).x, v2sub(s1, s2).y);
			if (left_ofline(s1, s2, cur))
				my_mlx_pixel_put(&a->img, u, v, v3_to_col((t_v3){0.0, 0.0, 0.0}));
			else if (left_ofline(s2, s3, cur))
				my_mlx_pixel_put(&a->img, u, v, v3_to_col((t_v3){0.0, 0.0, 0.0}));
			else if (left_ofline(s3, s1, cur))
				my_mlx_pixel_put(&a->img, u, v, v3_to_col((t_v3){0.0, 0.0, 0.0}));
			else
				my_mlx_pixel_put(&a->img, u, v, v3_to_col(col));
		}
	}

	printf("s1 sub s2 (%.3f, %.3f)\n", v2sub(s1, s2).x, v2sub(s1, s2).y);
	printf("s3: (%.3f, %.3f)\n", s3.x, s3.y);
	mlx_put_image_to_window(a->mlx_instance, a->window, a->img.img, 0, 0);
	a->mouse_pos_old = a->mouse_pos;
	bound(s1, 0, 1);
	bound(s2, 0, 1);
	bound(s3, 0, 1);
	usleep(1000);
	return (0);
}

static t_v2f	bound(t_v2f v, float min, float max)
{
	return ((t_v2f){fmaxf(fminf(v.x, max), min), fmaxf(fminf(v.y, max), min)});
}

static int	left_ofline(t_v2f s1, t_v2f s2, t_v2f cur)
{
	t_v2f	tmp;

	tmp = v2sub(s2, s1);
	return ((cur.x - s1.x) * tmp.y - (cur.y - s1.y) * tmp.x < 0);
}
