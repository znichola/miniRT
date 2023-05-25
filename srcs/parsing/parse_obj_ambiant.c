/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_ambiant.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:58:39 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/25 16:37:13 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_grammar_ambiant(t_token *tokens);
static void	consume_ambiant(t_token **tokens, t_object *obj);
static int	validate_and_reformat_ambiant(t_object *obj);

int	parse_ambiant(t_token **tokens, t_object *obj)
{
	int	res;

	res = check_grammar_ambiant(*tokens);
	if (res != 0)
		return (res);
	consume_ambiant(tokens, obj);
	if (validate_and_reformat_ambiant(obj) != 0)
		return (e_validation);
	return (0);
}

/* check if grammar for ambiant is valid */
static int	check_grammar_ambiant(t_token *tokens)
{
	return (check_line_grammar(tokens));
}

/* fill the object with the values from the tokens */
static void	consume_ambiant(t_token **tokens, t_object *obj)
{
	obj->type = e_ambiant;
	*tokens = (*tokens)->next;
	obj->object.a.ratio = (*tokens)->value.scalar;
	*tokens = (*tokens)->next;
	obj->object.a.colour = (*tokens)->value.pos;
	*tokens = (*tokens)->next;
	*tokens = (*tokens)->next;
}

/* check if values are valid */
static int	validate_and_reformat_ambiant(t_object *obj)
{
	t_ambiant	*a;

	a = &obj->object.a;
	if (a->ratio < 0 || a->ratio > 1)
		return (-1);
	if (validate_colour(&a->colour) != 0)
		return (-1);
	return (0);
}
