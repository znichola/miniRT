/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:59:41 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/20 23:44:30 by znichola         ###   ########.fr       */
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

enum e_tok_type
{
	e_vector,
	e_scalar,
	e_string,
	e_end_of_line,
	e_optional
};

enum e_optional_type
{
	e_texture,
	e_bump,
	e_normal,
	e_checker
};

typedef struct s_optional
{
	enum e_optional_type	type;
	char					*filepath;
}	t_optional;

union u_val
{
	const char	*str;
	t_v3		pos;
	float		scalar;
	t_optional	opt;
};


/* save the line number to give more interesting error messages */
typedef struct s_token
{
	enum e_tok_type	type;
	union u_val		value;
	int				line;
	struct s_token	*next;
}	t_token;

enum e_parse_error
{
	e_success = 0,
	e_empty,
	e_validation,
	e_missing_eol,
	e_missing_id,
	e_missing_vector,
	e_missing_scalar,
	e_invalid_id,
	e_eof
} ;

typedef struct s_error
{
	int			line;
	const char*	msg;
}	t_error;

/* primary parsing function */

int		parse(const char *filename, t_scene *scene);

/* tokenization */

t_token	*tokenize(int fd);
void	free_tokens(t_token *tok);

/* parse utils */

char		*get_word(const char **str);
int			is_only_whitespace(const char *str);
void		trim(const char **str);
const char	*ret_obj_string(t_object *o);

/* parse scalar*/

int		parse_int(const char **str, int *res);
int		parse_float(const char **str, float *res);

/* parse properties */

int		parse_position(const char **line, t_v3 *pos);
int		parse_colour(const char **line, t_v3 *clr);
int		parse_orientation(const char **line, t_v3 *orientation);
int		parse_ratio(const char **line, float *ratio);
int		parse_optional(const char **line, t_optional *opt);

/* parse objects */

int		parse_ambiant(t_token **lst, t_object *obj);
int		parse_camera(t_token **lst, t_object *obj);
int		parse_light(t_token **lst, t_object *obj);
int		parse_sphere(t_token **lst, t_object *obj);
int		parse_plane(t_token **lst, t_object *obj);
int		parse_cylinder(t_token **lst, t_object *obj);
int		parse_cone(t_token **tokens, t_object *obj);

/* scene */

void	init_scene(t_scene *scene);
void	cleanup_scene(t_scene *scene);
int		validate_scene(int state);

/* scene add object */

int		scene_add_object(t_scene *scene, t_object obj, int *state);

/* validate and reformat parsed properties */

int	validate_orientation(t_v3 *vec);
int	validate_colour(t_v3 *vec);

/* grammar check */
int	check_line_grammar(t_token *tokens);

#endif
