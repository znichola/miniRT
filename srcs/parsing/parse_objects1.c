/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:57:16 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/13 17:57:51 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_ambiant(const char **line)
{
	(void)line;
	printf("ambiant\n");
	return (0);
}

int	parse_camera(const char **line)
{
	(void)line;
	printf("camera\n");
	return (0);
}

int	parse_light(const char **line)
{
	(void)line;
	printf("light\n");
	return (0);
}