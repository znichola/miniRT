/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:43:17 by znichola          #+#    #+#             */
/*   Updated: 2023/05/11 14:10:44 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_v3(char *name, t_v3 v)
{
	printf("%s (%f, %f, %f)\n", name, v.x, v.y, v.z);
}

int	imin(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	imax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	print_image(t_app *a)
{
	for (int x = 0; x < a->img.width; x++)
		for (int y = 0; y < a->img.height; y++)
			my_mlx_pixel_put(&a->img, x, y, moon_texture(a, x, y));
	mlx_put_image_to_window(a->mlx_instance, a->window, a->img.img, 0, 0);

	usleep(100000);
}


static void	print_obj_list(t_list *l)
{
	t_object	*o;

	while (l)
	{
		o = l->content;
		printf("%s[%p] : ", ret_obj_string(o), o);
		print_v3("pos", get_obj_pos(o));
		l = l->next;
	}
}

void	print_scene(t_app *a)
{
	printf("\n>>> scene debug print <<<\n");
	print_v3("camera    position:", a->s.camera.position);
	print_v3("camera orientation:", a->s.camera.orientation);
	  printf("camera         fov: %.2f\n\n", a->s.camera.fov);

	print_v3("ambient     colour: ", a->s.ambiant.colour);
	  printf("ambient      ratio: %.2f\n\n", a->s.ambiant.ratio);

	printf("objects :\n");
	print_obj_list(a->s.objects_list);

	printf("\nlights: \n");
	print_obj_list(a->s.lights_list);

}
