/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 11:45:37 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/27 10:46:54 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		tokenize_line(t_token **lst, const char *line, int line_number);
static t_token	*tokenize_word(const char *word);
static t_token	*token_factory(int type, union u_val value, int line);

t_token	*tokenize(int fd)
{
	t_token	*lst;
	char	*line;
	int		i;

	lst = NULL;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		i++;
		tokenize_line(&lst, line, i);
		free(line);
		line = get_next_line(fd);
	}
	return (lst);
}

void	free_tokens(t_token *tok)
{
	t_token	*current;
	t_token	*next;

	current = tok;
	while (current)
	{
		next = current->next;
		if (current->type == e_string)
			free((void *)current->value.str);
		free(current);
		current = next;
	}
}

static void	tokenize_line(t_token **lst, const char *line, int line_number)
{
	char	*word;
	t_token	*tok;
	t_token	**current;

	current = lst;
	if (*current)
		current = &(*current)->next;
	while (1)
	{
		word = get_word(&line);
		printf("{%s}\n", word);
		if (!word || !*word)
		{
			tok = token_factory(e_end_of_line, (union u_val)0.0f, line_number);
			*current = tok;
			break;
		}
		tok = tokenize_word(word);
		tok->line = line_number;
		*current = tok;
		current = &(*current)->next;
	}
}

/* a bit ugly, no? */
static t_token *tokenize_word(const char *word)
{
	union u_val	value;
	const char	*cpy1;
	const char	*cpy2;

	cpy1 = word;
	cpy2 = word;
	if (parse_position(&cpy1, &value.pos) == 0)
	{
		return (token_factory(e_vector, value, -1));
	}
	else if (parse_float(&cpy2, &value.scalar) == 0)
	{
		return (token_factory(e_scalar, value, -1));
	}
	else
	{
		value.str = word;
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