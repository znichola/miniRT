/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:38:37 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/27 10:01:02 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_grammar_cylinder(t_token *tokens);
static void	consume_cylinder(t_token **tokens, t_object *obj);
static int	validate_and_reformat_cylinder(t_object *obj);

int	parse_cylinder(t_token **tokens, t_object *obj)
{
	int	res;

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
	if (tokens->type != e_string)
		return (e_missing_id);
	if (strcmp(tokens->value.str, "cy") != 0)
		return (e_invalid_id);
	tokens = tokens->next;
	if (tokens->type != e_vector)
		return (e_missing_vector);
	tokens = tokens->next;
	if (tokens->type != e_vector)
		return (e_missing_vector);
	tokens = tokens->next;
	if (tokens->type != e_scalar)
		return (e_missing_scalar);
	tokens = tokens->next;
	if (tokens->type != e_scalar)
		return (e_missing_scalar);
	tokens = tokens->next;
	if (tokens->type != e_vector)
		return (e_missing_vector);
	tokens = tokens->next;
	if (tokens->type != e_end_of_line)
		return (e_missing_eol);
	return (0);
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
	*tokens = (*tokens)->next; //skip the end-of-line token
}

/* check if values are valid */
static int	validate_and_reformat_cylinder(t_object *obj)
{
	t_cylinder	*cy;

	cy = &obj->object.cy;
	if (!validate_orientation(cy->orientation))
		return (-1);
	if (cy->radius < 0)
		return (-1);
	cy->radius /= 2;
	if (cy->height < 0)
		return (-1);
	if (!validate_colour(&cy->colour))
		return (-1);
	return (0);
}