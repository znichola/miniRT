/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:13:53 by znichola          #+#    #+#             */
/*   Updated: 2023/05/29 11:17:59 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	origin(void)
{
	return ((t_v3){0.0f, 0.0f, 0.0f});
}

t_v3	up(void)
{
	return ((t_v3){0.0f, 1.0f, 0.0f});
}

t_v3	right(void)
{
	return ((t_v3){1.0f, 0.0f, 0.0f});
}

t_v3	in(void)
{
	return ((t_v3){0.0f, 0.0f, 1.0f});
}

t_v3	checker_colour(void)
{
	return ((t_v3){1.0f, 1.0f, 1.0f});
}
