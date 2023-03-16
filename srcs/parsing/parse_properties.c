/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:00:15 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/16 16:28:49 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minirt_structs.h"

static t_v3	rgb_to_v3(int rgb[3]);

int	parse_position(const char **line, t_v3 *pos)
{
	if (parse_float(line, &pos->x) != 0)
		return (-1);
	if (**line != ',')
		return (-1);
	(*line)++;
	if (parse_float(line, &pos->y) != 0)
		return (-1);
	if (**line != ',')
		return (-1);
	(*line)++;
	if (parse_float(line, &pos->z) != 0)
		return (-1);
	return (0);
}

int	parse_color(const char **line, t_v3 *clr)
{
	int	rgb[3];

	if (parse_int(line, rgb + 0) != 0 || rgb[0] < 0 || rgb[0] > 255)
		return (-1);
	if (**line != ',')
		return (-1);
	(*line)++;

	if (parse_int(line, rgb + 1) != 0 || rgb[1] < 0 || rgb[1] > 255)
		return (-1);
	if (**line != ',')
		return (-1);
	(*line)++;

	if (parse_int(line, rgb + 2) != 0 || rgb[2] < 0 || rgb[2] > 255)
		return (-1);

	*clr = rgb_to_v3(rgb);
	return (0);
}

static t_v3	rgb_to_v3(int rgb[3])
{
	t_v3	clr;

	clr.x = (float)rgb[0]/255;
	clr.y = (float)rgb[1]/255;
	clr.z = (float)rgb[2]/255;
	return (clr);
}
