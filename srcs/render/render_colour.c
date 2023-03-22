/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_colour.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:16:08 by znichola          #+#    #+#             */
/*   Updated: 2023/03/22 13:16:26 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

typedef struct s_v2f
{
	float	x;
	float	y;
}	t_v2f;


int		v3_to_col(t_v3 v);
t_v3	col_add(t_v3 a, t_v3 b);
t_v3	col_multi(t_v3 a, t_v3 b);

t_v2f	v2sub(t_v2f a, t_v2f b);
t_v2f	v2add(t_v2f a, t_v2f b);
float	v2mag(t_v2f v);
t_v2f	bound(t_v2f v, float min, float max);
int		left_ofline(t_v2f s1, t_v2f s2, t_v2f cur);

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

int	v3_to_col(t_v3 v)
{
	return (create_trgb(0, v.x * 255, v.y * 255, v.z * 255));
}

t_v3	col_add(t_v3 a, t_v3 b)
{
	return ((t_v3){fminf(a.x + b.x, 1.0),
					fminf(a.y + b.y, 1.0),
					fminf(a.z + b.z, 1.0)});
}

t_v3	col_multi(t_v3 a, t_v3 b)
{
	return ((t_v3){fminf(a.x * b.x, 1.0),
					fminf(a.y * b.y, 1.0),
					fminf(a.z * b.z, 1.0)});
}

t_v2f	v2sub(t_v2f a, t_v2f b)
{
	return ((t_v2f){a.x - b.x, a.y - b.y});
}

t_v2f	v2add(t_v2f a, t_v2f b)
{
	return ((t_v2f){a.x + b.x, a.y + b.y});
}

float	v2mag(t_v2f v)
{
	return (hypot(v.x, v.y));
}

t_v2f	bound(t_v2f v, float min, float max)
{
	return ((t_v2f){fmaxf(fminf(v.x, max), min), fmaxf(fminf(v.y, max), min)});
}

int	left_ofline(t_v2f s1, t_v2f s2, t_v2f cur)
{
	t_v2f	tmp;

	tmp = v2sub(s2, s1);
	return ((cur.x - s1.x) * tmp.y - (cur.y - s1.y) * tmp.x < 0);
}
