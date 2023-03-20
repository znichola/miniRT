/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:57:19 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/20 14:56:43 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minirt.h"

#define AMBIANT		0
#define CAMERA		1
#define LIGHT		2
#define SPHERE		3
#define PLANE		4
#define CYLINDER	5

static int	parse_line(const char *line, t_object *obj);
static int	parse_scene(int fd, const char *filename, t_scene *scene);
static int	parse_identifier(const char **line, int *id);

int	parse(const char *filename, t_scene *scene)
{
	int		fd;
	int		res;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("filename");
		exit(1);
	}
	res = parse_scene(fd, filename, scene);
	close(fd);
	return (res);
}

static int	parse_scene(int fd, const char *filename, t_scene *scene)
{
	char		*line;
	int			i;
	int			res;
	t_object	obj;
	int			state;

	state = 0;
	init_scene(scene);
	line = get_next_line(fd);
	i = 0;
	res = 0;
	while (i++, line)
	{
		if (!is_only_whitespace(line))
		{
			res = parse_line(line, &obj);
			if (res == 0)
				res = scene_add_object(scene, obj, &state);
		}
		free(line);
		if (res != 0)
		{
			print_error(res, i, filename);
			break ;
		}
		line = get_next_line(fd);
	}
	if (res == 0)
	{
		res = validate_scene(state);
		if (res != 0)
			print_error(res, -1, filename);
	}
	return (res);
}

static int	parse_line(const char *line, t_object *obj)
{
	if (parse_identifier(&line, &obj->type) != 0)
		return (ERROR_INVALID_ID);
	if (obj->type == AMBIANT)
	{
		if (parse_ambiant(&line, &obj->object.a) != 0)
			return (ERROR_SYNTAX);
	}
	else if (obj->type == CAMERA)
	{
		if (parse_camera(&line, &obj->object.c) != 0)
			return (ERROR_SYNTAX);
	}
	else if(obj->type == LIGHT)
	{
		if (parse_light(&line, &obj->object.l) != 0)
			return (ERROR_SYNTAX);
	}
	else if (obj->type == SPHERE)
	{
		if (parse_sphere(&line, &obj->object.sp) != 0)
			return (ERROR_SYNTAX);
	}
	else if (obj->type == PLANE)
	{
		if (parse_plane(&line, &obj->object.pl) != 0)
			return (ERROR_SYNTAX);
	}
	else if (obj->type == CYLINDER)
	{
		if (parse_cylinder(&line, &obj->object.cy) != 0)
			return (ERROR_SYNTAX);
	}
	else
		return (-1);
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
		return (-1);

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
	return (0);
}
