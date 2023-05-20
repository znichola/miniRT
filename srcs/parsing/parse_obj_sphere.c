/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:59:31 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/17 15:46:32 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_grammar_sphere(t_token *tokens);
static void	consume_sphere(t_token **tokens, t_object *obj);
static int	validate_and_reformat_sphere(t_object *obj);
static void consume_optional_sphere(t_token **tokens, t_sphere *sp);

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
	return (check_line_grammar(tokens));
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

	consume_optional_sphere(tokens, &obj->object.sp);

	*tokens = (*tokens)->next; //skip the end-of-line token
}

static void consume_optional_sphere(t_token **tokens, t_sphere *sp)
{
	sp->texture.filepath = NULL;
	sp->bump.filepath = NULL;
	sp->normal.filepath = NULL;
	sp->checker = 0;
	while (*tokens && (*tokens)->type == e_optional)
	{
		if ((*tokens)->value.opt.type == e_texture)
			sp->texture.filepath = ft_strdup((*tokens)->value.opt.filepath);
		else if ((*tokens)->value.opt.type == e_bump)
			sp->bump.filepath = ft_strdup((*tokens)->value.opt.filepath);
		else if ((*tokens)->value.opt.type == e_normal)
			sp->normal.filepath = ft_strdup((*tokens)->value.opt.filepath);
		else if ((*tokens)->value.opt.type == e_checker)
			sp->checker = ft_strcmp((*tokens)->value.opt.filepath, "true") == 0;
		*tokens = (*tokens)->next;
	}
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