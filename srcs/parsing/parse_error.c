/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:28:49 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/20 14:51:52 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_error(int err, int line_num, const char *filename)
{
	if (err == ERROR_INVALID_ID)
		printf("Error\n%s: Invalid identifier on line %d\n",
			filename, line_num);
	else if (err == ERROR_DUPLICATE_ID)
		printf("Error\n%s: Forbidden duplicate identifier on line %d\n",
			filename, line_num);
	else if (err == ERROR_MISSING_A)
		printf("Error\n%s: Missing required identifier `A'\n", filename);
	else if (err == ERROR_MISSING_C)
		printf("Error\n%s: Missing required identifier `C'\n", filename);
	else if (err == ERROR_SYNTAX)
		printf("Error\n%s: Syntax error on line %d\n", filename, line_num);
	else if (err != 0)
		printf("Error\n");
}
