/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:57:16 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/21 15:50:39 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minirt_structs.h"
#include <math.h>

int	parse_fov(const char **line, float *fov);

/*
	Ambiant light has 2 properties:
		- ratio in range [0,1] (which we verify)
		- colour in rgb values (which we convert to [0, 1] ratios)
*/
int	parse_ambiant(const char **line, t_ambiant *a)
{
	trim(line);
	if (parse_float(line, &a->ratio) != 0)
		return (ERROR_SYNTAX);
	if (a->ratio < 0 || a->ratio > 1)
		return (ERROR_SYNTAX);
	trim(line);
	if (parse_colour(line, &a->colour) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (**line != '\0')
		return (ERROR_SYNTAX);
	return (0);
}

/*
	Camera has 3 properties:
		- position (vector 3)
		- orientation (vector 3 in range [0, 1])
		- field of view in range [0, 180]
*/
int	parse_camera(const char **line, t_camera *c)
{
	trim(line);
	if (parse_position(line, &c->position) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (parse_orientation(line, &c->orientation) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (parse_fov(line, &c->fov) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (**line != '\0')
		return (ERROR_SYNTAX);
	return (0);
}

/*
	Light has 3 properties:
		- position
		- ratio in range [0, 1]
		- colour in rgb
*/
int	parse_light(const char **line, t_light *l)
{
	trim(line);
	if (parse_position(line, &l->position) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (parse_ratio(line, &l->ratio) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (parse_colour(line, &l->colour) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (**line != '\0')
		return (ERROR_SYNTAX);
	return (0);
}

int	parse_fov(const char **line, float *fov)
{
	int	fov_in_degrees;

	if (parse_int(line, &fov_in_degrees) != 0)
		return (-1);
	if (fov_in_degrees <= 0 || fov_in_degrees > 180)
		return (-1);
	*fov = (float)fov_in_degrees * (M_PI/180);
	return (0);
}