/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:34:26 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/22 15:52:03 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/* Unit tests using the Check framework */

int	main(int argc, char **argv)
{
	int number_failed = 0;

	if (argc != 2)
	{
		printf("Please specify which tests you'd like to run\n");
		return (1);
	}

	/* parsing tests*/
	if (strcmp(argv[1], "parsing") == 0)
	{
		Suite *s0 = parse_float_suite();
		Suite *s1 = parse_position_suite();
		Suite *s2 = parse_color_suite();
		Suite *s3 = parse_objects_suite();
		Suite *s4 = parse_suite();

		SRunner *sr = srunner_create(s0);
		srunner_add_suite(sr, s1);
		srunner_add_suite(sr, s2);
		srunner_add_suite(sr, s3);
		srunner_add_suite(sr, s4);

		srunner_run_all(sr, CK_NORMAL);
		number_failed = srunner_ntests_failed(sr);
		srunner_free(sr);
	}

	/* maths tests */
	else if (strcmp(argv[1], "maths") == 0)
	{
		Suite *m0 = poi_sphere_suite();

		SRunner *maths_runner = srunner_create(m0);

		srunner_run_all(maths_runner, CK_NORMAL);
		number_failed = srunner_ntests_failed(maths_runner);
		srunner_free(maths_runner);
	}
	return (number_failed == 0)? EXIT_SUCCESS: EXIT_FAILURE;
}