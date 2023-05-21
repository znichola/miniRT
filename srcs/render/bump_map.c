/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 10:34:33 by znichola          #+#    #+#             */
/*   Updated: 2023/05/21 22:02:26 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_v3	get_pixel_below(t_img_data *texture, t_v2f point);
static t_v3	get_pixel_right(t_img_data *texture, t_v2f point);

/*
	we are multiplying the normal vector by 3 to get it more pronounced
*/
t_v3	get_bmp_adjusted_normal(t_object *o, t_intersection *i)
{
	float		pix;
	float		below;
	float		to_right;
	t_img_data	*bmp;
	t_v3		bmp_normal;

	bmp = get_obj_bmp(o);
	pix = get_pix_from_texture(bmp, i->map).x;
	to_right = get_pixel_right(bmp, i->map).x;
	below = get_pixel_below(bmp, i->map).x;
	bmp_normal = v3_unitvec((t_v3){pix - to_right, pix - below, 1});
	return (v3_unitvec(v3_add(i->poi_normal, v3_multiply(bmp_normal, 1))));
}

t_img_data	*get_obj_bmp(t_object *o)
{
	if (o->type == e_sphere)
		return (&o->object.sp.bump);
	else if (o->type == e_cylinder)
		return (&o->object.cy.bump);
	else if (o->type == e_plane)
		return (&o->object.pl.bump);
	else if (o->type == e_cone)
		return (&o->object.co.bump);
	return (NULL);
}

static t_v3	get_pixel_below(t_img_data *texture, t_v2f point)
{
	unsigned int	pix;
	t_v3			clr;
	int				x;
	int				y;

	if (point.x > 1 || point.x < 0)
		point.x = fabsf(fmodf(point.x, 1.0f));
	if (point.y > 1 || point.y < 0)
		point.y = fabsf(fmodf(point.x, 1.0f));
	x = texture->width * point.x;
	y = texture->height * point.y + 1;
	if (y <= texture->height)
		y = texture->height - 1;
	// printf("(%.2f, %.2f) -> (%d, %d)\n", point.x, point.y, x, y);
	pix = *(unsigned int *)(texture->addr + (y * texture->line_length +
		x *(texture->bits_per_pixel / 8)));
	clr.x = (float)get_r(pix) / 255.0f;
	clr.y = (float)get_g(pix) / 255.0f;
	clr.z = (float)get_b(pix) / 255.0f;
	return (clr);
}

static t_v3	get_pixel_right(t_img_data *texture, t_v2f point)
{
	unsigned int	pix;
	t_v3			clr;
	int				x;
	int				y;

	if (point.x > 1 || point.x < 0)
		point.x = fabsf(fmodf(point.x, 1.0f));
	if (point.y > 1 || point.y < 0)
		point.y = fabsf(fmodf(point.x, 1.0f));
	x = texture->width * point.x + 1;
	if (x >= texture->width)
		x = texture->width - 1;
	y = texture->height * point.y;
	// printf("(%.2f, %.2f) -> (%d, %d)\n", point.x, point.y, x, y);
	pix = *(unsigned int *)(texture->addr + (y * texture->line_length +
		x *(texture->bits_per_pixel / 8)));
	clr.x = (float)get_r(pix) / 255.0f;
	clr.y = (float)get_g(pix) / 255.0f;
	clr.z = (float)get_b(pix) / 255.0f;
	return (clr);
}
