/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:22:08 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/21 11:00:19 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static	int	len_word(const char *str);

//unused!!
t_list	*tokenize(const char *str)
{
	t_list	*lst;
	t_list	*new_item;
	char	*word;

	lst = NULL;
	while (1)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == '\0')
			break ;
		word = get_word(&str);
		if (!word)
			exit(1);
		new_item = ft_lstnew(word);
		if (!new_item)
			exit(1);
		ft_lstadd_back(&lst, new_item);
	}
	return (lst);
}

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
