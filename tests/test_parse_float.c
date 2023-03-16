/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:41:15 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/16 13:51:40 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static void	test(const char *str, int expected_res)
{
	const char *cpy = str;
	float f_expected = atof(cpy);
	float f_actual;
	if (parse_float(&cpy, &f_actual) != expected_res)
		ck_abort_msg("result of parse_float() does not match with {%s}", str);
	if (expected_res == 0)
		ck_assert_float_eq_tol(f_expected, f_actual, 0.0005);
	ck_assert(!isdigit(*cpy));
}

START_TEST(basic_0)
{
	test("0", 0);
	test("00.0", 0);
	test("0.000000000", 0);
}
END_TEST

START_TEST(basic_1)
{
	test("1234514", 0);
	test("253723.198291829", 0);
	test("0.0000273672", 0);
}
END_TEST

START_TEST(basic_2)
{
	test("1681616 17", 0);
	test("1234a0", 0);
	test("2372738237X", 0);
	test("12815	", 0);
	test("0.5\n", 0);
}
END_TEST

START_TEST(basic_3)
{
	test("+17", 0);
	test("+1.0", 0);
	test("+0123.16271268", 0);
}
END_TEST

START_TEST(basic_4)
{
	test("-17", 0);
	test("-1.0", 0);
	test("-0123.16271268", 0);
}
END_TEST

START_TEST(invalid_0)
{
	test("ABC1681616 17", -1);
	test("  1234a", -1);
	test("", -1);
	test(".", -1);
	test("+-+", -1);
}
END_TEST

START_TEST(invalid_1)
{
	test("ABC168161..17", -1);
	test("1..1", -1);
	test("0.+", -1);
	test(".", -1);
	test("-.", -1);
}
END_TEST

Suite	*float_suite(void)
{
	Suite	*s;
	TCase	*tc_basic;
	TCase	*tc_invalid;

	s = suite_create("parse_float()");

	tc_basic = tcase_create("basic");
	tcase_add_test(tc_basic, basic_0);
	tcase_add_test(tc_basic, basic_1);
	tcase_add_test(tc_basic, basic_2);
	tcase_add_test(tc_basic, basic_3);
	tcase_add_test(tc_basic, basic_4);
	suite_add_tcase(s, tc_basic);

	tc_invalid = tcase_create("invalid");
	tcase_add_test(tc_invalid, invalid_0);
	tcase_add_test(tc_invalid, invalid_1);
	suite_add_tcase(s, tc_invalid);
	return (s);
}
