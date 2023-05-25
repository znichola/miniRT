/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:58:17 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/25 16:41:40 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	load_object(t_app *a, t_list *objects);

void	load_all_textures(t_app *a)
{
	t_list	*objects;

	objects = a->s.objects_list;
	while (objects)
	{
		load_object(a, objects);
		objects = objects->next;
	}
}

static void	load_object(t_app *a, t_list *objects)
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
	if (((int)(point.x / (1.0 / 26)) % 2) == ((int)(point.y / (1.0 / 26)) % 2))
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
		point.x = fabsf(fmodf(point.x, 1.0f));
	if (point.y > 1 || point.y < 0)
		point.y = fabsf(fmodf(point.x, 1.0f));
	x = texture->width * point.x;
	y = texture->height * point.y;
	pix = *(unsigned int *)(texture->addr + (y * texture->line_length
				+ x *(texture->bits_per_pixel / 8)));
	clr.x = (float)get_r(pix) / 255.0f;
	clr.y = (float)get_g(pix) / 255.0f;
	clr.z = (float)get_b(pix) / 255.0f;
	return (clr);
}
