/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:04:20 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/17 11:38:03 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "parsing.h"

static void	test(const char *str, float r, float g, float b, int res)
{
	t_v3	clr;

	if (parse_colour(&str, &clr) != res)
	{
		ck_abort_msg("res code don't match");
	}
	else if (res == 0)
	{
		ck_assert_float_eq_tol(clr.x, r, 0.01);
		ck_assert_float_eq_tol(clr.y, g, 0.01);
		ck_assert_float_eq_tol(clr.z, b, 0.01);
	}
	ck_assert(!isdigit(*str));

}

START_TEST(valid0)
{
	test("0,0,0", 0, 0, 0, 0);
	test("255,255,255", 1, 1, 1, 0);
	test("128,128,128", 0.5, 0.5, 0.5, 0);
}
END_TEST

START_TEST(valid1)
{
	test("120,100,10", (float)120/255, (float)100/255, (float)10/255, 0);
	test("120,100,10ABC", (float)120/255, (float)100/255, (float)10/255, 0);
	test("254,9,173  ", (float)254/255, (float)9/255, (float)173/255, 0);
}
END_TEST

START_TEST(invalid0)
{
	test("-120,100,10", 0,0,0,-1);
	test("0,256,-1", 0,0,0,-1);
	test("255,255,23143254132416251",0,0,0,-1);
}
END_TEST

START_TEST(invalid1)
{
	test("ABC0,0,0",0,0,0,-1);
	test("  255,10,0 ", 0,0,0,-1);
	test(",0,0", 0,0,0,-1);
}

START_TEST(invalid2)
{
	test("0.0,250.10,0",0,0,0,-1);
	test("34.,617,,0", 0,0,0,-1);
	test("45,09,.45", 0,0,0,-1);
}

Suite	*parse_color_suite(void)
{
	Suite	*s;
	TCase	*tc_valid;
	TCase	*tc_invalid;

	s = suite_create("parse_colour()");

	tc_valid = tcase_create("valid");
	tcase_add_test(tc_valid, valid0);
	tcase_add_test(tc_valid, valid1);
	suite_add_tcase(s, tc_valid);

	tc_invalid = tcase_create("invalid");
	tcase_add_test(tc_invalid, invalid0);
	tcase_add_test(tc_invalid, invalid1);
	tcase_add_test(tc_invalid, invalid2);
	suite_add_tcase(s, tc_invalid);

	return (s);
}