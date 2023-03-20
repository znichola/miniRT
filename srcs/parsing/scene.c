/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:03:32 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/20 14:42:31 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"
# include "libft.h"

#define AMBIANT		0
#define CAMERA		1
#define LIGHT		2
#define SPHERE		3
#define PLANE		4
#define CYLINDER	5

#define MASK_AMBIANT	1
#define MASK_CAMERA		2

static int	scene_add_ambiant(t_scene *scene, t_object obj, int *state);
static int	scene_add_camera(t_scene *scene, t_object obj, int *state);
static int	scene_add_light(t_scene *scene, t_object obj);
static int	scene_add_other(t_scene *scene, t_object obj);

void	init_scene(t_scene *scene)
{
	scene->lights_list = NULL;
	scene->objects_list = NULL;
}

void	cleanup_scene(t_scene *scene)
{
	ft_lstclear(&scene->lights_list, free);
	ft_lstclear(&scene->objects_list, free);
}

int	validate_scene(int state)
{
	if (!(state & MASK_AMBIANT))
		return (ERROR_MISSING_A);
	if (!(state & MASK_CAMERA))
		return (ERROR_MISSING_C);
	return (0);
}

/*
	add object to scene

	state is a variable that is used to keep track of whether we already have
	an ambiant light or camera.
*/
int	scene_add_object(t_scene *scene, t_object obj, int *state)
{
	if (obj.type == AMBIANT)
		return (scene_add_ambiant(scene, obj, state));
	else if (obj.type == CAMERA)
		return (scene_add_camera(scene, obj, state));
	else if (obj.type == LIGHT)
		return (scene_add_light(scene, obj));
	else
		return (scene_add_other(scene, obj));
}

static int	scene_add_ambiant(t_scene *scene, t_object obj, int *state)
{
	if (*state & MASK_AMBIANT)
		return (ERROR_DUPLICATE_ID);
	ft_memcpy(&scene->ambiant, &obj.object.a, sizeof(t_ambiant));
	*state |= MASK_AMBIANT;
	return (0);
}

static int	scene_add_camera(t_scene *scene, t_object obj, int *state)
{
	if (*state & MASK_CAMERA)
		return (ERROR_DUPLICATE_ID);
	ft_memcpy(&scene->camera, &obj.object.c, sizeof(t_camera));
	*state |= MASK_CAMERA;
	return (0);
}

static int	scene_add_light(t_scene *scene, t_object obj)
{
	t_light	*l;
	t_list	*node;

	l = malloc(sizeof(*l));
	ft_memcpy(l, &obj.object.l, sizeof(t_light));
	node = ft_lstnew(l);
	if (!node)
		exit(1);
	ft_lstadd_front(&scene->lights_list, node);
	return (0);
}

static int	scene_add_other(t_scene *scene, t_object obj)
{
	t_list		*node;
	t_object	*cpy;

	cpy = malloc(sizeof(*cpy));
	ft_memcpy(cpy, &obj, sizeof(*cpy));
	node = ft_lstnew(cpy);
	if (!node)
		exit(1);
	ft_lstadd_front(&scene->objects_list, node);
	return (0);
}
