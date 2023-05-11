/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:20:38 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/11 15:21:40 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static enum e_tok_type	*get_obj_grammar(int obj_id);
static int	check_obj_grammar(t_token *tokens, enum e_tok_type *grammar);
static int	get_error_enum(int token_enum);

int	check_line_grammar(t_token *tokens)
{
	const char	*obj_ids[6] = {"A", "C", "L", "sp", "pl", "cy"};
	int			i;

	if (!tokens)
		return (e_eof);
	if (tokens->type != e_string)
		return (e_missing_id);
	i = -1;
	while (++i < 6)
	{
		if (ft_strcmp(tokens->value.str, obj_ids[i]) == 0)
			break ;
	}
	return (check_obj_grammar(tokens->next, get_obj_grammar(i)));
}

/*
	return the objects grammar, 8 is the current max tokens feel free to
	change if you need more.
	each objects grammar should always be terminated by e_end_of_line
*/
static enum e_tok_type	*get_obj_grammar(int obj_id)
{
	static enum e_tok_type	grammar[6][8] = {
/* ambient */	{e_scalar, e_vector, e_end_of_line},
/* camera  */	{e_vector, e_vector, e_scalar, e_end_of_line},
/* light   */	{e_vector, e_scalar, e_vector, e_end_of_line},
/* sphere  */	{e_vector, e_scalar, e_vector, e_optional, e_end_of_line},
/* plane   */	{e_vector, e_vector, e_vector, e_optional, e_end_of_line},
/* cylinder*/	{e_vector, e_vector, e_scalar, e_scalar, e_vector, e_optional, e_end_of_line}};

	if (obj_id < 0 || obj_id >= 6)
	{
		printf("\"%d\" is an invalid obj_id, stupid programmer", obj_id);
		exit(42);
	}
	return (grammar[obj_id]); /* this ugly ass +1 is to ignore the e_object that's usefull for the initial writing of the grammar */
}

/*
	follows the grammar given as a list of token enums
*/
static int	check_obj_grammar(t_token *tokens, enum e_tok_type *grammar)
{
	while (tokens && *grammar != e_end_of_line)
	{
		if (*grammar == e_optional && tokens->type != e_optional)
		{
			grammar++;
			continue;
		}
		if (*grammar == e_optional && tokens->type == e_optional)
		{
			tokens = tokens->next;
			continue;
		}
		if (*grammar != tokens->type)
		{
			return (get_error_enum(*grammar));
		}
		tokens = tokens->next;
		grammar++;
	}
	if (!tokens)
		return (e_eof);
	if (tokens->type != e_end_of_line)
		return (get_error_enum(e_end_of_line));
	return (0);
}

static int	get_error_enum(int token_enum)
{
	const int	token[4] = {e_vector, e_scalar, e_string, e_end_of_line};
	const int	error[4] = {e_missing_vector, e_missing_scalar, e_missing_id, e_eof};
	int			i;

	i = 4;
	while (--i >= 0)
		if (token[i] == token_enum)
			return (error[i]);
	printf("\"%d\" is an invalid error enum, stupid prgrammer", token_enum);
	exit(42);
	return (0);
}
