/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:59:19 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/26 14:51:04 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	consume_plane(t_token **tokens, t_object *obj);
static int	validate_and_reformat_plane(t_object *obj);
static void	consume_optional_plane(t_token **tokens, t_plane *pl);

int	parse_plane(t_token **tokens, t_object *obj)
{
	int	res;

	res = check_line_grammar(*tokens, e_plane);
	if (res != 0)
		return (res);
	consume_plane(tokens, obj);
	res = validate_and_reformat_plane(obj);
	return (res);
}

/* fill the object with the values from the tokens */
static void	consume_plane(t_token **tokens, t_object *obj)
{
	obj->type = e_plane;
	*tokens = (*tokens)->next;
	obj->object.pl.position = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	obj->object.pl.orientation = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	obj->object.pl.colour = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	consume_optional_plane(tokens, &obj->object.pl);
	*tokens = (*tokens)->next;
}

static void	consume_optional_plane(t_token **tokens, t_plane *pl)
{
	pl->texture.filepath = NULL;
	pl->bump.filepath = NULL;
	pl->normal.filepath = NULL;
	pl->checker = 0;
	while (*tokens && (*tokens)->type == e_optional)
	{
		if ((*tokens)->value.opt.type == e_texture)
			pl->texture.filepath = ft_strdup((*tokens)->value.opt.filepath);
		else if ((*tokens)->value.opt.type == e_bump)
			pl->bump.filepath = ft_strdup((*tokens)->value.opt.filepath);
		else if ((*tokens)->value.opt.type == e_normal)
			pl->normal.filepath = ft_strdup((*tokens)->value.opt.filepath);
		else if ((*tokens)->value.opt.type == e_checker)
			pl->checker = ft_strcmp((*tokens)->value.opt.filepath, "true") == 0;
		*tokens = (*tokens)->next;
	}
}

/* check if values are valid */
static int	validate_and_reformat_plane(t_object *obj)
{
	t_plane	*pl;

	pl = &obj->object.pl;
	if (validate_orientation(&pl->orientation) != 0)
		return (e_invalid_orientation);
	if (validate_colour(&pl->colour) != 0)
		return (e_invalid_colour);
	return (0);
}
