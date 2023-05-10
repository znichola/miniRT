/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:00:15 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/10 10:41:24 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minirt_structs.h"
#include "minirt_maths.h"

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

int	parse_colour(const char **line, t_v3 *clr)
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

	clr.x = (float)rgb[0] / 255;
	clr.y = (float)rgb[1] / 255;
	clr.z = (float)rgb[2] / 255;
	return (clr);
}

int	parse_orientation(const char **line, t_v3 *vec)
{
	if (parse_position(line, vec) != 0)
		return (-1);
	if (vec->x == 0 && vec->y == 0 && vec->z == 0)
		return (-1);
	*vec = v3_unitvec(*vec);
	return (0);
}

int	parse_ratio(const char **line, float *ratio)
{
	if (parse_float(line, ratio) != 0)
		return (-1);
	if (*ratio < 0 || *ratio > 1)
		return (-1);
	return (0);
}

int	parse_optional(const char **line, t_optional *opt)
{
	const char	*tokens[] = {"texture", "bump", "normal"};

	int i = 0;
	while (i < 3)
	{
		if (ft_strncmp(tokens[i], *line, ft_strlen(tokens[i])) == 0)
		{
			*line += ft_strlen(tokens[i]);
			break;
		}
		i++;
	}
	if (i == 3)
		return (-1);
	opt->type = i;
	if (**line != ':')
		return (-1);
	(*line)++;
	opt->filepath = ft_strdup(*line);
	return (0);
}