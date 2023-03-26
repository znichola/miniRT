/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:38:37 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/26 14:38:37 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cylinder(t_token **tokens, t_object *obj)
{
	int	res;

	res = check_grammar_cylinder(*tokens);
	if (res != 0)
		return (res);
	consume_cylinder(tokens, obj);
	if (validate_and_reformat_cylinder(obj) != 0)
		return (E_VALIDATION_ERROR);
}

/* check if grammar for cylinder is valid */
static int check_grammar_cylinder(t_token *tokens)
{
	if (tokens->type != e_string)
		return (E_MISSING_ID);
	if (strcmp(tokens->value.str, "cy") != 0)
		return (E_INVALID_ID);
	tokens = tokens->next;
	if (tokens->type != e_vector)
		return (E_MISSING_VECTOR);
	tokens = tokens->next;
	if (tokens->type != e_vector)
		return (E_MISSING_VECTOR);
	tokens = tokens->next;
	if (tokens->type != e_scalar)
		return (E_MISSING_SCALAR);
	tokens = tokens->next;
	if (tokens->type != e_scalar)
		return (E_MISSING_SCALAR);
	tokens = tokens->next;
	if (tokens->type != e_vector)
		return (E_MISSING_VECTOR);
	tokens = tokens->next;
	if (tokens->type != e_end_of_line)
		return (E_MISSING_EOL);
	return (0);
}

/* fill the object with the values from the tokens */
static void	consume_cylinder(t_token **tokens, t_object *obj)
{
	obj->type = e_cylinder;
	*tokens = (*tokens)->next; //skip the identifier
	obj->content.cy.position = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	obj->content.cy.orientation = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	obj->content.cy.radius = (*tokens)->value.scalar;
	*tokens = (*tokens)->next;
	obj->content.cy.height = (*tokens)->value.scalar;
	*tokens = (*tokens)->next;
	obj->content.cy.colour = (*tokens)->value.pos;
	*tokens = (*tokens)->next; //skip the end-of-line token
}

/* check if values are valid */
static int	validate_and_reformat_cylinder(t_object *obj)
{
	t_cylinder	*cy;

	cy = &obj->content.cy;
	if (!validate_orientation(cy->orientation))
		return (-1);
	if (cy->radius < 0)
		return (-1);
	cy->radius /= 2;
	if (cy->height < 0)
		return (-1);
	if (!validate_colour(cy->colour))
		return (-1);
	return (0);
}