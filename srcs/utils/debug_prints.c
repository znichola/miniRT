/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:43:17 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 16:32:04 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_v3(char *name, t_v3 v)
{
	printf("%s (%.2f, %.2f, %.2f)\n", name, v.x, v.y, v.z);
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

static void	print_lights_list(t_list *l)
{
	t_object o;
	t_light	light;

	while (l)
	{
		light = *(t_light *)l->content;
		o.type = e_light;
		o.object.l = light;
		printf("%s[%p] : ", ret_obj_string(&o), l);
		print_v3("pos", get_obj_pos(&o));
		l = l->next;
	}
}

void	print_scene(t_app *a)
{
	printf("\n>>> scene debug print <<<\n");
	print_v3("camera    position:", a->s.camera.position);
	print_v3("camera orientation:", a->s.camera.orientation);
	  printf("camera         fov: %.2f\n\n", a->s.camera.fov);

	print_v3("ambient     colour:", a->s.ambiant.colour);
	  printf("ambient      ratio: %.2f\n\n", a->s.ambiant.ratio);

	printf("objects\n");
	print_obj_list(a->s.objects_list);

	printf("\nlights\n");
	print_lights_list(a->s.lights_list);

}

void	print_m4(t_m4 m)
{
	t_t4	t;
	int		i;
	int		j;

	t = m4_to_t(&m);
	i = 0;
	while (i < 4)
	{
		printf("| ");
		j = 0;
		while (j < 4)
		{
			printf("%8.5f ", t.m[i][j]);
			j++;
		}
		printf("|\n");
		i++;
	}
}
