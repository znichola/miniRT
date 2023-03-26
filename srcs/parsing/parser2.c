/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 13:04:14 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/26 13:04:14 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_object(t_list **tokens, t_object *obj);

int	parser2(t_list *tokens, t_scene *scene)
{
	t_object	obj;
	int			state;
	int			res;

	res = 0;
	state = 0;
	while (res == 0 || res == E_EMPTY)
	{
		res = parse_object(&tokens, &obj);
		if (res != 0)
			res = scene_add_object(scene, obj, &state);
	}
	if (res == 0 || res == E_EMPTY)
		res = validate_scene(state);
	return (res);
}

static int	parse_object(t_list **tokens, t_object *obj)
{
	int	res;

	if (!*tokens)
		return (E_END_OF_INPUT);
	if ((*tokens)->type = e_end_of_line)
		return (E_EMPTY);
	res = parse_ambiant(tokens, obj);
	if (res == E_INVALID_ID)
		res = parse_camera(tokens, obj);
	if (res == E_INVALID_ID)
		res = parse_light(tokens, obj);
	if (res == E_INVALID_ID)
		res = parse_sphere(tokens, obj);
	if (res == E_INVALID_ID)
		res = parse_plane(tokens, obj);
	if (res == E_INVALID_ID)
		res = parse_cylinder(tokens, obj);
	if (res != 0)
		printf("Error during parsing\n");
	return (res);
}
