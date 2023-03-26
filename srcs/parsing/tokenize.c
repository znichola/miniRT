/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 11:45:37 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/26 11:45:37 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

enum e_tok_type
{
	e_vector,
	e_scalar,
	e_string,
	e_end_of_line
};

union u_val
{
	char	*str;
	t_v3	pos;
	float	scalar;
};

/* save the line number to give more interesting error messages */
typedef struct s_token
{
	enum e_tok_type	type;
	union u_val		value;
	int				line;
	struct s_token	*next;
}	t_token;

static void		tokenize_line(t_token **lst, char *line, int line_number);
static t_token *tokenize_word(char *word);
static t_token *token_factory(int type, union u_val value, int line);

t_token	*tokenize(int fd)
{
	t_token	*lst;
	char	*word;
	char	*line;
	int		i;

	lst = NULL;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		i++;
		tokenize_line(&lst, line, i);
	}
	return (lst);
}

static void	tokenize_line(t_token **lst, char *line, int line_number)
{
	char	*word;
	t_token	*tok;
	t_token	**current;

	current = lst;
	while (1)
	{
		word = get_word(&line);
		if (!word || !*word)
		{
			tok = token_factory(e_end_of_line, (union u_val)0, line_number);
			(*current)->next = tok;
			break;
		}
		tok = tokenize_word(word);
		tok->line = line_number;
		(*current)->next = tok;
		current = &(*current)->next;
	}
}

static t_token *tokenize_word(char *word)
{
	union u_val	value;

	if (parse_position(&word, &value.pos) == 0)
	{
		return (token_factory(e_vector, value, -1));
	}
	else if (parse_float(&word, &value.scalar) == 0)
	{
		return (token_factory(e_scalar, value, -1));
	}
	else
	{
		value.s = word;
		return (token_factory(e_string, value, -1));
	}
}

static t_token *token_factory(int type, union u_val value, int line)
{
	t_token	*tok;

	tok = malloc(sizeof(*tok));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	tok->line = line;
	tok->next = NULL;
	return (tok);
}