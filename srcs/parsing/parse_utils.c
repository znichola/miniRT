/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:22:08 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/25 16:40:25 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static	int	len_word(const char *str);

char	*get_word(const char **str)
{
	char	*word;
	int		len;
	int		i;

	len = len_word(*str);
	if (len == 0)
		return (0);
	word = malloc(len + 1);
	if (!word)
		return (0);
	while (ft_isspace(**str))
		(*str)++;
	i = 0;
	while (i < len)
		word[i++] = *(*str)++;
	word[i] = 0;
	return (word);
}

static	int	len_word(const char *str)
{
	int	i;

	while (ft_isspace(*str))
		str++;
	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

int	is_only_whitespace(const char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return (*str == '\0');
}

void	trim(const char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}

const char	*ret_obj_string(t_object *o)
{
	const char	*types[MRT_NUM_OBJ_TYPES] = {
		"ambiant",
		"camera",
		"light",
		"sphere",
		"plane",
		"cylinder",
		"cone"
	};

	if (o->type < 0 || o->type >= MRT_NUM_OBJ_TYPES)
	{
		printf("%d not a valid object type enum somehow !?\n", o->type);
		return ("bad_type");
	}
	return (types[o->type]);
}
