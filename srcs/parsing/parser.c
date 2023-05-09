/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 13:04:14 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/09 13:05:15 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_object(t_token **tokens, t_object *obj);
static int	parser2(t_token *tokens, t_scene *scene);

int	parse(const char *filename, t_scene *scene)
{
	int		fd;
	int		res;
	t_token	*tok_list;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("filename");
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
	int			res;

	res = 0;
	state = 0;
	int i = 0;
	while (res == 0 && tokens)
	{
		res = parse_object(&tokens, &obj);
		if (res == 0)
			res = scene_add_object(scene, obj, &state);
		else
			printf("error with object: %i\n", i);
		i++;
	}
	if (res == 0)
		res = validate_scene(state);
	if (res != 0)
		printf("Error: %d\n", res);
	return (res);
}

static int	parse_object(t_token **tokens, t_object *obj)
{
	int	res;

	res = parse_ambiant(tokens, obj);
	if (res == e_invalid_id)
		res = parse_camera(tokens, obj);
	if (res == e_invalid_id)
		res = parse_light(tokens, obj);
	if (res == e_invalid_id)
		res = parse_sphere(tokens, obj);
	if (res == e_invalid_id)
		res = parse_plane(tokens, obj);
	if (res == e_invalid_id)
		res = parse_cylinder(tokens, obj);
	return (res);
}
