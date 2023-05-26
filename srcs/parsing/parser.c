/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 13:04:14 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/26 15:18:29 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_error	parse_object(t_token **tokens, t_object *obj);
static int		parser2(t_token *tokens, t_scene *scene);

int	parse(const char *filename, t_scene *scene)
{
	int		fd;
	int		res;
	t_token	*tok_list;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
	{
		perror(filename);
		exit(1);
	}
	tok_list = tokenize(fd);
	res = parser2(tok_list, scene);
	free_tokens(tok_list);
	close(fd);
	return (res);
}

static int	parser2(t_token *tokens, t_scene *scene)
{
	t_object	obj;
	int			state;
	t_error		res;
	int			i;

	res = (t_error){-1, 0};
	state = 0;
	i = 0;
	while (res.error == 0 && tokens)
	{
		res = parse_object(&tokens, &obj);
		if (res.error == 0)
			res.error = scene_add_object(scene, obj, &state);
		i++;
	}
	if (res.error == 0)
		res.error = validate_scene(state);
	print_error(res);
	return (res.error);
}

static t_error	parse_object(t_token **tokens, t_object *obj)
{
	const char	*obj_ids[MRT_NUM_OBJ_TYPES] = {
		"A", "C", "L", "sp", "pl", "cy", "co"};
	int			i;
	static int	(*f[MRT_NUM_OBJ_TYPES])(t_token **, t_object *) = {
		parse_ambiant,
		parse_camera,
		parse_light,
		parse_sphere,
		parse_plane,
		parse_cylinder,
		parse_cone
	};

	if (!*tokens)
		return ((t_error){(*tokens)->line, e_eof});
	if ((*tokens)->type != e_string)
		return ((t_error){(*tokens)->line, e_missing_id});
	i = -1;
	while (++i < MRT_NUM_OBJ_TYPES)
	{
		if (ft_strcmp((*tokens)->value.str, obj_ids[i]) == 0)
			return ((t_error){(*tokens)->line, f[i](tokens, obj)});
	}
	return ((t_error){(*tokens)->line, e_invalid_id});
}
