/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:59:41 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/16 16:09:57 by skoulen          ###   ########.fr       */
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

int		parse(const char *filename);

/* parse utils */
char	*get_word(const char **str);
int		is_only_whitespace(const char *str);

/* parse scalar*/
int		parse_int(const char **str, int *res);
int		parse_float(const char **str, float *res);

/* parse properties */
int		parse_position(const char **line, t_v3 *pos);
int		parse_color(const char **line, t_v3 *clr);

/* parse objects */
int		parse_ambiant(const char **line);
int		parse_camera(const char **line);
int		parse_light(const char **line);
int		parse_sphere(const char **line);
int		parse_plane(const char **line);
int		parse_cylinder(const char **line);

#endif