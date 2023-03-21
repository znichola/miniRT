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

int		parse(const char *filename, t_scene *scene);

/* parse utils */
t_list	*tokenize(const char *str);
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
int		parse_ambiant(const char **line, t_ambiant *a);
int		parse_camera(const char **line, t_camera *c);
int		parse_light(const char **line, t_light *l);
int		parse_sphere(const char **line, t_sphere *sp);
int		parse_plane(const char **line, t_plane *pl);
int		parse_cylinder(const char **line, t_cylinder *cy);

/* scene */
void	init_scene(t_scene *scene);
void	cleanup_scene(t_scene *scene);
int		validate_scene(int state);

/* scene add object */
int		scene_add_object(t_scene *scene, t_object obj, int *state);

/* parse error */
void	print_error(int err, int line_num, const char *filename);

#endif