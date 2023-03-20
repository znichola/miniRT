/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scalar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:47:24 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/16 14:13:16 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	parse_float_before(const char **str, float *res);
static int	parse_float_after(const char **str, float *res);

/*
	Parse an integer and advance the pointer.
	TODO: check for overflow
*/
int	parse_int(const char **str, int *res)
{
	if (!ft_isdigit(**str))
		return (-1);
	*res = ft_atoi(*str);
	while (ft_isdigit(**str))
		(*str)++;
	return (0);
}

/*
	Parse a float and advance the pointer.
	Is there some overflow checking to do?
*/
int	parse_float(const char **str, float *res)
{
	if (parse_float_before(str, res) != 0)
		return (-1);
	if (**str != '.')
		return (0);
	(*str)++;
	if (parse_float_after(str, res) != 0)
		return (-1);
	return (0);
}

/* parse what is before the point in a float */
static int	parse_float_before(const char **str, float *res)
{
	float	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (*(*str)++ == '-')
			sign = -1;
	}
	if (!ft_isdigit(**str))
		return (-1);
	*res = 0;
	while (ft_isdigit(**str))
	{
		*res *= 10;
		*res += ((float)(**str - '0')) * sign;
		(*str)++;
	}
	return (0);
}

/* parse what is after the point in a float */
static int	parse_float_after(const char **str, float *res)
{
	float	i;
	float	sign;

	if (!ft_isdigit(**str))
		return (-1);
	sign = 1;
	if (*res < 0)
		sign = -1;
	i = 10;
	while (ft_isdigit(**str))
	{
		*res += ((float)(**str - '0')) * sign * 1 / i;
		i *= 10;
		(*str)++;
	}
	return (0);
}
