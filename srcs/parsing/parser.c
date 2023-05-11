/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 13:04:14 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/11 13:38:37 by znichola         ###   ########.fr       */
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
	const char	*obj_ids[6] = {"C", "L", "A", "cy", "pl", "sp"};
	int			i;

	if (!*tokens)
		return (e_eof);
	if ((*tokens)->type != e_string)
		return (e_missing_id);
	i = -1;
	while (++i < 6)
	{
		if (ft_strcmp((*tokens)->value.str, obj_ids[i]) == 0)
			break ;
	}
	if (i == 0)
		return (parse_camera(tokens, obj));
	else if (i == 1)
		return (parse_light(tokens, obj));
	else if (i == 2)
		return (parse_ambiant(tokens, obj));
	else if (i == 3)
		return (parse_cylinder(tokens, obj));
	else if (i == 4)
		return (parse_plane(tokens, obj));
	else if (i == 5)
		return (parse_sphere(tokens, obj));
	else
		return (e_invalid_id);
}
