/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:03:32 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/26 15:07:26 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

#define MASK_AMBIANT	1
#define MASK_CAMERA		2

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
		return (e_no_ambiant);
	if (!(state & MASK_CAMERA))
		return (e_no_camera);
	printf("SCENE OKAY\n");
	return (0);
}
