/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:57:19 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/13 17:58:53 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minirt.h"

static int	parse_line(const char *line);
static int	parse_identifier(const char **line, int *id);

int	parse(const char *filename)
{
	int		fd;
	char	*line;
	int		res;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("filename");
		exit(1);
	}

	line = get_next_line(fd);
	res = 0;
	while (line)
	{
		res = parse_line(line);
		free(line);
		line = get_next_line(fd);
	}

	close(fd);
	return (res);
}

#define AMBIANT		0
#define CAMERA		1
#define LIGHT		2
#define SPHERE		3
#define PLANE		4
#define CYLINDER	5

static int	parse_line(const char *line)
{
	int	id;

	if (is_only_whitespace(line))
		return (0);

	if (parse_identifier(&line, &id) != 0)
		return (-1);

	if (id == AMBIANT)
		parse_ambiant(&line);
	else if (id == CAMERA)
		parse_camera(&line);
	else if(id == LIGHT)
		parse_light(&line);
	else if (id == SPHERE)
		parse_sphere(&line);
	else if (id == PLANE)
		parse_plane(&line);
	else
		parse_cylinder(&line);
	return (0);
}

#define ID_COUNT 6

static int	parse_identifier(const char **line, int *id)
{
	const char	*ids[] = {
		"A", "C", "L", "sp", "pl", "cy"
	};
	int			i;
	char		*token;

	token = get_word(line);
	if (!token)
	{
		printf("syntax error: unexpected end of line\n"); //line number?
		return (-1);
	}

	i = 0;
	while (i < ID_COUNT)
	{
		if (ft_strcmp(ids[i], token) == 0)
			break ;
		i++;
	}

	free(token);

	if (i == ID_COUNT)
		return (-1);
	*id = i;
	printf("id<%s>\n", ids[i]);
	return (0);
}
