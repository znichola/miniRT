/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:00:15 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/16 11:35:24 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	parse_position(const char **line, t_v3 *pos)
{
	pos->x = parse_float(line);
	if (**line != ',')
		return (-1);
	pos->y = parse_float(line);
	if (**line != ',')
		return (-1);
	pos->z = parse_float(line);
	if (**line && !ft_isspace(**line))
		return (-1);
}

int	parse_color(const char **line, t_v3 *clr)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(*line);
	while (ft_isdigit(**line))
		(*line)++;
	if (**line != ',')
		return (-1);
	(*line)++;

	g = ft_atoi(*line);
	while (ft_isdigit(**line))
		(*line)++;
	if (**line != ',')
		return (-1);
	(*line)++;

	b = ft_atoi(*line);
	while (ft_isdigit(**line))
		(*line)++;
	if (**line && !ft_isspace(**line))
		return (-1);

	*clr = rgb_to_v3(r, g, b);
	return (0);
}

static int	rgb_to_v3(int r, int g, int b)
{

}
