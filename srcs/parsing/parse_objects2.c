/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:58:01 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/21 15:40:52 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	parse_radius(const char **line, float *radius);

/*
	Sphere has 3 properties:
		- position,
		- diameter (must be >= 0)
		- colour
*/
int	parse_sphere(const char **line, t_sphere *sp)
{
	trim(line);
	if (parse_position(line, &sp->position) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (parse_radius(line, &sp->radius) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (parse_colour(line, &sp->colour) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (**line != '\0')
		return (ERROR_SYNTAX);
	return (0);
}

/*
	Plane has 3 properties:
		- position
		- orientation
		- colour
*/
int	parse_plane(const char **line, t_plane *pl)
{
	trim(line);
	if (parse_position(line, &pl->position) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (parse_orientation(line, &pl->orientation) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (parse_colour(line, &pl->colour) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (**line != '\0')
		return (ERROR_SYNTAX);
	return (0);
}

/*
	Cylinder has 5 properties:
		- position
		- orientation
		- diameter (must be >= 0)
		- height (must be >= 0)
		- colour
*/
int	parse_cylinder(const char **line, t_cylinder *cy)
{
	trim(line);
	if (parse_position(line, &cy->position) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (parse_orientation(line, &cy->orientation) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (parse_radius(line, &cy->radius) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (parse_float(line, &cy->height) != 0)
		return (ERROR_SYNTAX);
	if (cy->height <= 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (parse_colour(line, &cy->colour) != 0)
		return (ERROR_SYNTAX);
	trim(line);
	if (**line != '\0')
		return (ERROR_SYNTAX);
	return (0);
}

static int	parse_radius(const char **line, float *radius)
{
	if (parse_float(line, radius) != 0)
		return (-1);
	if (*radius <= 0)
		return (-1);
	*radius /= 2;
	return (0);
}