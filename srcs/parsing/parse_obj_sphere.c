/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:59:31 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/09 14:19:13 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_grammar_sphere(t_token *tokens);
static void	consume_sphere(t_token **tokens, t_object *obj);
static int	validate_and_reformat_sphere(t_object *obj);

int	parse_sphere(t_token **tokens, t_object *obj)
{
	int	res;

	printf("SPHERE\n");
	res = check_grammar_sphere(*tokens);
	if (res != 0)
		return (res);
	consume_sphere(tokens, obj);
	if (validate_and_reformat_sphere(obj) != 0)
		return (e_validation);
	return (0);
}

/* check if grammar for sphere is valid */
static int	check_grammar_sphere(t_token *tokens)
{
	if (tokens->type != e_string)
		return (e_missing_id);

	if (strcmp(tokens->value.str, "sp") != 0)
		return (e_invalid_id);
	tokens = tokens->next;

	if (tokens->type != e_vector) //position
		return (e_missing_vector);
	tokens = tokens->next;

	if (tokens->type != e_scalar) //diameter
		return (e_missing_scalar);
	tokens = tokens->next;

	if (tokens->type != e_vector) //colour
		return (e_missing_vector);
	tokens = tokens->next;

	if (tokens->type != e_end_of_line)
		return (e_missing_eol);
	return (0);
}

/* fill the object with the values from the tokens */
static void	consume_sphere(t_token **tokens, t_object *obj)
{
	obj->type = e_sphere;
	*tokens = (*tokens)->next; //skip the identifier
	obj->object.sp.position = (*tokens)->value.pos;

	*tokens = (*tokens)->next;
	obj->object.sp.radius = (*tokens)->value.scalar;

	*tokens = (*tokens)->next;
	obj->object.sp.colour = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	*tokens = (*tokens)->next; //skip the end-of-line token
}

/* check if values are valid */
static int	validate_and_reformat_sphere(t_object *obj)
{
	t_sphere	*sp;

	sp = &obj->object.sp;

	if (sp->radius < 0)
		return (-1);
	sp->radius /= 2;

	if (validate_colour(&sp->colour) != 0)
		return (-1);
	return (0);
}