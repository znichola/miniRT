/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:58:01 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/17 17:55:08 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_sphere(const char **line, t_sphere *sp)
{
	while (ft_isspace(**line))
		(*line)++;
	if (parse_position(line, &sp->position) != 0)
		return (-1);
	while (ft_isspace(**line))
		(*line)++;
	if (parse_float(line, &sp->diameter) != 0)
		return (-1);
	if (sp->diameter <= 0)
		return (-1);
	while (ft_isspace(**line))
		(*line)++;
	if (parse_colour(line, &sp->colour) != 0)
		return (-1);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != '\0')
		return (-1);
	return (0);
}

int	parse_plane(const char **line, t_plane *pl)
{
	while (ft_isspace(**line))
		(*line)++;
	if (parse_position(line, &pl->position) != 0)
		return (-1);
	while (ft_isspace(**line))
		(*line)++;
	if (parse_orientation(line, &pl->orientation) != 0)
		return (-1);
	while (ft_isspace(**line))
		(*line)++;
	if (parse_colour(line, &pl->colour) != 0)
		return (-1);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != '\0')
		return (-1);
	return (0);
}

int	parse_cylinder(const char **line, t_cylinder *cy)
{
	while (ft_isspace(**line))
		(*line)++;
	if (parse_position(line, &cy->position) != 0)
		return (-1);
	while (ft_isspace(**line))
		(*line)++;
	if (parse_orientation(line, &cy->orientation) != 0)
		return (-1);
	while (ft_isspace(**line))
		(*line)++;
	if (parse_float(line, &cy->diameter) != 0)
		return (-1);
	if (cy->diameter <= 0)
		return (-1);
	while (ft_isspace(**line))
		(*line)++;
	if (parse_float(line, &cy->height) != 0)
		return (-1);
	if (cy->height <= 0)
		return (-1);
	while (ft_isspace(**line))
		(*line)++;
	if (parse_colour(line, &cy->colour) != 0)
		return (-1);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != '\0')
		return (-1);
	return (0);
}
