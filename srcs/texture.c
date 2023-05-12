/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:58:17 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/12 17:40:29 by skoulen          ###   ########.fr       */
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

t_v3	get_pix_from_checkerboard(t_v2f point)
{
	if (point.x < 0)
		point.x -= 1;
	if (point.y < 0)
		point.y -= 1;
	if ((int)(floor(point.x * 25) + floor(point.y * 25)) % 2)
		return ((t_v3){0,0,0});
	else
		return ((t_v3){255,255,255});
}

t_v3	get_pix_from_texture(t_img_data *texture, t_v2f point)
{
	unsigned int	pix;
	t_v3			clr;
	int				x;
	int				y;

	point.x += 0.4;
	x = texture->width * point.x;
	y = texture->height * point.y;
	pix = *(unsigned int *)(texture->addr + (y * texture->line_length +
		x *(texture->bits_per_pixel / 8)));
	clr.x = get_r(pix);
	clr.y = get_g(pix);
	clr.z = get_b(pix);
	return (clr);
}
