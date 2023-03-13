/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:57:19 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/13 15:28:53 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	parse_line(const char *line);
static int	parse_identifier(const char **line);

int	parse(const char *filename)
{
	int	fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("filename");
		exit(1);
	}

	line = get_next_line(fd);
	while (line)
	{
		parse_line(line);
		free(line);
		line = get_next_line(fd);
	}

	close(fd);
	return (0);
}

static int	parse_line(const char *line)
{
	if (parse_identifier(&line))
		return (-1);
	return (0);
}

#define ID_COUNT 6

static int	parse_identifier(const char **line)
{
	const char * ids[] = {
		"A", "C", "L", "sp", "pl", "cy"
	};
	int	i;

	while (ft_isspace(**line))
		(*line)++;
	i = 0;
	while (i < ID_COUNT)
	{
		if ((ft_strncmp(ids[i], *line, ft_strlen(ids[i])) == 0)
			&& (!*(*line + ft_strlen(ids[i]))
				|| ft_isspace(*(*line + ft_strlen(ids[i])))))
			break ;
			i++;
	}
	if (i == ID_COUNT)
		return (-1);
	printf("id<%s>\n", ids[i]);
	return (0);
}