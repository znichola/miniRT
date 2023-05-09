/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:59:00 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/09 14:03:18 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_grammar_light(t_token *tokens);
static void	consume_light(t_token **tokens, t_object *obj);
static int	validate_and_reformat_light(t_object *obj);

int	parse_light(t_token **tokens, t_object *obj)
{
	int	res;

	printf("LIGHT\n");
	res = check_grammar_light(*tokens);
	if (res != 0)
		return (res);
	consume_light(tokens, obj);
	if (validate_and_reformat_light(obj) != 0)
		return (e_validation);
	return (0);
}

/* check if grammar for light is valid */
static int	check_grammar_light(t_token *tokens)
{
	if (tokens->type != e_string)
		return (e_missing_id);
	if (strcmp(tokens->value.str, "L") != 0)
		return (e_invalid_id);
	tokens = tokens->next;
	if (tokens->type != e_vector) //position
		return (e_missing_vector);

	tokens = tokens->next;
	if (tokens->type != e_scalar) //ratio
		return (e_missing_scalar);

	tokens = tokens->next;
	if (tokens->type != e_vector) //color
		return (e_missing_vector);

	tokens = tokens->next;
	if (tokens->type != e_end_of_line)
		return (e_missing_eol);
	return (0);
}

/* fill the object with the values from the tokens */
static void	consume_light(t_token **tokens, t_object *obj)
{
	obj->type = e_light;
	*tokens = (*tokens)->next; //skip the identifier
	obj->object.l.position = (*tokens)->value.pos;

	*tokens = (*tokens)->next;
	obj->object.l.ratio = (*tokens)->value.scalar;


	*tokens = (*tokens)->next;
	obj->object.l.colour = (*tokens)->value.pos;
	*tokens = (*tokens)->next;

	*tokens = (*tokens)->next; //skip the end-of-line token
}

/* check if values are valid */
static int	validate_and_reformat_light(t_object *obj)
{
	t_light	*l;

	l = &obj->object.l;

	if (l->ratio < 0 || l->ratio > 1)
		return (-1);

	if (validate_colour(&l->colour) != 0)
		return (-1);
	return (0);
}