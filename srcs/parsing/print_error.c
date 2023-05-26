/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:25:51 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/26 15:13:12 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_parse_error(t_error e);
static void	print_validation_error(t_error e);
static void	print_scene_error(t_error e);

void	print_error(t_error e)
{
	print_parse_error(e);
	print_validation_error(e);
	print_scene_error(e);
}

static void	print_parse_error(t_error e)
{
	if (e.error == e_invalid_id)
		printf("Parse error: invalid id on line %d\n", e.line);
	else if (e.error == e_missing_eol)
		printf("Parse error: missing newline on line %d\n", e.line);
	else if (e.error == e_missing_id)
		printf("Parse error: missing id on line %d\n", e.line);
	else if (e.error == e_missing_vector)
		printf("Parse error: missing vector on line %d\n", e.line);
	else if (e.error == e_missing_scalar)
		printf("Parse error: missing scalar value on line %d\n", e.line);
	else if (e.error == e_eof)
		printf("Parse error: Unexpected end of file on line %d\n", e.line);
}

static void	print_validation_error(t_error e)
{
	if (e.error == e_invalid_orientation)
		printf("Validation error: invalid orientation on line: %d\n", e.line);
	else if (e.error == e_invalid_fov)
		printf("Validation error: invalid FOV on line: %d\n", e.line);
	else if (e.error == e_invalid_colour)
		printf("Validation error: invalid colour on line: %d\n", e.line);
	else if (e.error == e_invalid_ratio)
		printf("Validation error: invalid ratio on line: %d\n", e.line);
	else if (e.error == e_invalid_length)
		printf("Validation error: invalid length on line: %d\n", e.line);
}

static void	print_scene_error(t_error e)
{
	if (e.error == e_multi_ambiant)
		printf("Scene is invalid: multiple ambient objects\n");
	else if (e.error == e_multi_camera)
		printf("Scene is invalid: multiple camera objects\n");
	else if (e.error == e_no_ambiant)
		printf("Scene is invalid: no ambient object\n");
	else if (e.error == e_no_camera)
		printf("Scene is invalid: no camera object\n");
}
