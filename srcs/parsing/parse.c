/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:57:19 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/21 10:58:44 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minirt.h"

static int	parse_line(const char *line, t_object *obj);
static int	parse_scene(int fd, const char *filename, t_scene *scene);
static int	parse_identifier(const char **line, t_obj_type *id);

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

static int	parse_scene(int fd, const char *filename, t_scene *sc)
{
	char		*line;
	int			i;
	int			res;
	t_object	obj;
	int			state;

	state = 0;
	init_scene(sc);
	i = 0;
	res = 0;
	line = get_next_line(fd);
	while (i++, line)
	{
		if (!is_only_whitespace(line))
			res = (parse_line(line, &obj) || scene_add_object(sc, obj, &state));
		free(line);
		if (res != 0)
			break ;
		line = get_next_line(fd);
	}
	res = (res || validate_scene(state));
	print_error(res, i, filename);
	return (res);
}

static int	parse_line(const char *line, t_object *obj)
{
	int	res;

	if (parse_identifier(&line, &obj->type) != 0)
		return (ERROR_INVALID_ID);
	res = 0;
	if (obj->type == e_ambiant)
		res = parse_ambiant(&line, &obj->object.a);
	else if (obj->type == e_camera)
		res = parse_camera(&line, &obj->object.c);
	else if (obj->type == e_light)
		res = parse_light(&line, &obj->object.l);
	else if (obj->type == e_sphere)
		res = parse_sphere(&line, &obj->object.sp);
	else if (obj->type == e_plane)
		res = parse_plane(&line, &obj->object.pl);
	else if (obj->type == e_cylinder)
		res = parse_cylinder(&line, &obj->object.cy);
	else
		res = -1;
	return (res);
}

#define ID_COUNT 6

static int	parse_identifier(const char **line, t_obj_type *id)
{
	const char	*ids[] = {
		"A", "C", "L", "sp", "pl", "cy"
	};
	int			i;
	int			len;

	len = 0;
	i = 0;
	while (i < ID_COUNT)
	{
		len = ft_strlen(ids[i]);
		if (ft_strncmp(ids[i], *line, len) == 0 && ft_isspace(*(*line + len)))
			break ;
		i++;
	}
	if (i == ID_COUNT)
		return (-1);
	*id = i;
	*line += len;
	return (0);
}
