/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:58:17 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/21 10:26:34 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	load_all_textures(t_app *a)
{
	t_list	*objects;

	objects = a->s.objects_list;
	while (objects)
	{
		if (((t_object *)(objects->content))->type == e_sphere)
		{
			load_texture(a, &((t_object *)(objects->content))->object.sp.texture);
			load_texture(a, &((t_object *)(objects->content))->object.sp.bump);
			load_texture(a, &((t_object *)(objects->content))->object.sp.normal);
		}
		else if (((t_object *)(objects->content))->type == e_plane)
		{
			load_texture(a, &((t_object *)(objects->content))->object.pl.texture);
			load_texture(a, &((t_object *)(objects->content))->object.pl.bump);
			load_texture(a, &((t_object *)(objects->content))->object.pl.normal);
		}
		else if (((t_object *)(objects->content))->type == e_cylinder)
		{
			load_texture(a, &((t_object *)(objects->content))->object.cy.texture);
			load_texture(a, &((t_object *)(objects->content))->object.cy.bump);
			load_texture(a, &((t_object *)(objects->content))->object.cy.normal);
		}
		else if (((t_object *)(objects->content))->type == e_cone)
		{
			load_texture(a, &((t_object *)(objects->content))->object.cy.texture);
			load_texture(a, &((t_object *)(objects->content))->object.cy.bump);
			load_texture(a, &((t_object *)(objects->content))->object.cy.normal);
		}
		objects = objects->next;
	}
}

void	load_texture(t_app	*app, t_img_data *texture)
{
	if (texture->filepath == NULL)
	{
		texture->img = (void *)0;
		return ;
	}
	texture->img = mlx_xpm_file_to_image(&app->mlx_instance, texture->filepath,
		&texture->width, &texture->height);
	if (texture->img == NULL)
	{
		printf("failed to load texture: %s\n", texture->filepath);
		exit(1);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
		&texture->line_length, &texture->endian);
}

int	get_pix_from_checkerboard(t_v2f point)
{
	if (((int)(point.x / (1.0/26)) % 2) == ((int)(point.y / (1.0/26)) % 2))
		return (1);
	else
		return (0);
}

t_v3	get_pix_from_texture(t_img_data *texture, t_v2f point)
{
	unsigned int	pix;
	t_v3			clr;
	int				x;
	int				y;

	if (point.x > 1 || point.x < 0)
		point.x = fabsf(fmodf(point.x, 0.99f));
	if (point.y > 1 || point.y < 0)
		point.y = fabsf(fmodf(point.x, 0.99f));
	x = texture->width * point.x;
	y = texture->height * point.y;
	// printf("(%.2f, %.2f) -> (%d, %d)\n", point.x, point.y, x, y);
	pix = *(unsigned int *)(texture->addr + (y * texture->line_length +
		x *(texture->bits_per_pixel / 8)));
	clr.x = (float)get_r(pix) / 255.0f;
	clr.y = (float)get_g(pix) / 255.0f;
	clr.z = (float)get_b(pix) / 255.0f;
	return (clr);
}

/*
	this puts the three colours we need in a t_v3
	the point colour is in x
	the point above  is in y
	and to the right is in z
*/
// t_v3	get_adjacent_pixels(t_img_data *texture, t_v2f point)
// {
// 	unsigned int	pix;
// 	t_v3			clr;
// 	int				x;
// 	int				y;

// 	point.x += 0.4;
// 	x = texture->width * point.x;
// 	y = texture->height * point.y;
// 	pix = *(unsigned int *)(texture->addr + (y * texture->line_length +
// 		x *(texture->bits_per_pixel / 8)));
// 	clr.x = pix;
// 	pix = *(unsigned int *)(texture->addr + ((y + 1) * texture->line_length +
// 		x *(texture->bits_per_pixel / 8)));
// 	clr.y = pix;
// 	pix = *(unsigned int *)(texture->addr + (y * texture->line_length +
// 		(x + 1) *(texture->bits_per_pixel / 8)));
// 	clr.z;
// 	return (clr);
// }
