/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:38:37 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/17 15:46:04 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_grammar_cylinder(t_token *tokens);
static void	consume_cylinder(t_token **tokens, t_object *obj);
static int	validate_and_reformat_cylinder(t_object *obj);
static void consume_optional_cylinder(t_token **tokens, t_cylinder *cy);

int	parse_cylinder(t_token **tokens, t_object *obj)
{
	int	res;

	printf("CYLINDER\n");
	res = check_grammar_cylinder(*tokens);
	if (res != 0)
		return (res);
	consume_cylinder(tokens, obj);
	if (validate_and_reformat_cylinder(obj) != 0)
		return (e_validation);
	return (0);
}

/* check if grammar for cylinder is valid */
static int	check_grammar_cylinder(t_token *tokens)
{
	return (check_line_grammar(tokens));
}

/* fill the object with the values from the tokens */
static void	consume_cylinder(t_token **tokens, t_object *obj)
{
	obj->type = e_cylinder;
	*tokens = (*tokens)->next; //skip the identifier
	obj->object.cy.position = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	obj->object.cy.orientation = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	obj->object.cy.radius = (*tokens)->value.scalar;
	*tokens = (*tokens)->next;
	obj->object.cy.height = (*tokens)->value.scalar;
	*tokens = (*tokens)->next;
	obj->object.cy.colour = (*tokens)->value.pos;
	*tokens = (*tokens)->next;

	consume_optional_cylinder(tokens, &obj->object.cy);

	*tokens = (*tokens)->next; //skip the end-of-line token
}

static void consume_optional_cylinder(t_token **tokens, t_cylinder *cy)
{
	cy->texture.filepath = NULL;
	cy->bump.filepath = NULL;
	cy->normal.filepath = NULL;
	cy->checker = 0;
	while (*tokens && (*tokens)->type == e_optional)
	{
		if ((*tokens)->value.opt.type == e_texture)
			cy->texture.filepath = ft_strdup((*tokens)->value.opt.filepath);
		else if ((*tokens)->value.opt.type == e_bump)
			cy->bump.filepath = ft_strdup((*tokens)->value.opt.filepath);
		else if ((*tokens)->value.opt.type == e_normal)
			cy->normal.filepath = ft_strdup((*tokens)->value.opt.filepath);
		else if ((*tokens)->value.opt.type == e_checker)
			cy->checker = ft_strcmp((*tokens)->value.opt.filepath, "true") == 0;
		*tokens = (*tokens)->next;
	}
}

/* check if values are valid */
static int	validate_and_reformat_cylinder(t_object *obj)
{
	t_cylinder	*cy;

	cy = &obj->object.cy;
	if (validate_orientation(&cy->orientation) != 0)
		return (-1);
	if (cy->radius < 0)
		return (-1);
	cy->radius /= 2;
	if (cy->height < 0)
		return (-1);
	if (validate_colour(&cy->colour) != 0)
		return (-1);
	return (0);
}