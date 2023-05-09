/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:38:37 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/09 14:51:12 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_grammar_cylinder(t_token *tokens);
static void	consume_cylinder(t_token **tokens, t_object *obj);
static int	validate_and_reformat_cylinder(t_object *obj);

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

	*tokens = (*tokens)->next; //skip the end-of-line token
}

/* check if values are valid */
static int	validate_and_reformat_cylinder(t_object *obj)
{
	t_cylinder	*cy;

	cy = &obj->object.cy;
	if (validate_orientation(cy->orientation) != 0)
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