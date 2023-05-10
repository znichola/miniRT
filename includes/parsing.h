/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:59:41 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/21 10:52:49 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

# include "get_next_line.h"
# include "libft.h"
# include "minirt_structs.h"
# include "minirt_defines.h"

# define ERROR_INVALID_ID	1
# define ERROR_DUPLICATE_ID	2
# define ERROR_MISSING_A	3
# define ERROR_MISSING_C	4
# define ERROR_SYNTAX		5

enum e_tok_type
{
	e_vector,
	e_scalar,
	e_string,
	e_end_of_line
};

union u_val
{
	char	*str;
	t_v3	pos;
	float	scalar;
};

/* save the line number to give more interesting error messages */
typedef struct s_token
{
	enum e_tok_type	type;
	union u_val		value;
	int				line;
	struct s_token	*next;
}	t_token;

int		parse(const char *filename, t_scene *scene);

/* parse utils */
char	*get_word(const char **str);
int		is_only_whitespace(const char *str);
void	trim(const char **str);

/* parse scalar*/
int		parse_int(const char **str, int *res);
int		parse_float(const char **str, float *res);

/* parse properties */
int		parse_position(const char **line, t_v3 *pos);
int		parse_colour(const char **line, t_v3 *clr);
int		parse_orientation(const char **line, t_v3 *orientation);
int		parse_ratio(const char **line, float *ratio);

/* parse objects */
int		parse_ambiant(t_token **lst, t_object *obj);
int		parse_camera(t_token **lst, t_object *obj);
int		parse_light(t_token **lst, t_object *obj);
int		parse_sphere(t_token **lst, t_object *obj);
int		parse_plane(t_token **lst, t_object *obj);
int		parse_cylinder(t_token **lst, t_object *obj);

/* scene */
void	init_scene(t_scene *scene);
void	cleanup_scene(t_scene *scene);
int		validate_scene(int state);

/* scene add object */
int		scene_add_object(t_scene *scene, t_object obj, int *state);

/* parse error */
void	print_error(int err, int line_num, const char *filename);

#endif