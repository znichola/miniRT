/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:04:44 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/13 15:40:13 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		return (42);
	printf("parsing test: file %s\n", argv[1]);
	if (parse(argv[1]))
		printf("parse error\n");
	else
		printf("parse success\n");
}
