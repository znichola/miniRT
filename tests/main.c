/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:34:26 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/16 16:09:27 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main()
{
	printf("Unit tests with the check framework\n");

	int number_failed;
	Suite	*s0;
	Suite	*s1;
	Suite	*s2;
	SRunner	*sr;

	s0 = parse_float_suite();
	s1 = parse_position_suite();
	s2 = parse_color_suite();

	sr = srunner_create(s0);
	srunner_add_suite(sr, s1);
	srunner_add_suite(sr, s2);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0)? EXIT_SUCCESS: EXIT_FAILURE;
}