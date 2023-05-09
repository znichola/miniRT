/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:59:19 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/09 14:50:28 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_grammar_plane(t_token *tokens);
static void	consume_plane(t_token **tokens, t_object *obj);
static int	validate_and_reformat_plane(t_object *obj);

int	parse_plane(t_token **tokens, t_object *obj)
{
	int	res;

	printf("PLANE\n");
	res = check_grammar_plane(*tokens);
	if (res != 0)
		return (res);
	consume_plane(tokens, obj);
	if (validate_and_reformat_plane(obj) != 0)
		return (e_validation);
	return (0);
}

/* check if grammar for plane is valid */
static int	check_grammar_plane(t_token *tokens)
{
	return (check_line_grammar(tokens));
}

/* fill the object with the values from the tokens */
static void	consume_plane(t_token **tokens, t_object *obj)
{
	obj->type = e_plane;
	*tokens = (*tokens)->next; //skip the identifier
	obj->object.pl.position = (*tokens)->value.pos;

	*tokens = (*tokens)->next;
	obj->object.pl.orientation = (*tokens)->value.pos;

	*tokens = (*tokens)->next;
	obj->object.pl.colour = (*tokens)->value.pos;
	*tokens = (*tokens)->next;

	*tokens = (*tokens)->next; //skip the end-of-line token
}

/* check if values are valid */
static int	validate_and_reformat_plane(t_object *obj)
{
	t_plane	*pl;

	pl = &obj->object.pl;
	if (validate_orientation(pl->orientation) != 0)
		return (-1);

	if (validate_colour(&pl->colour) != 0)
		return (-1);
	return (0);
}