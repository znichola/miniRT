/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_position.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:41:25 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/16 16:03:58 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "parsing.h"

static void	test(const char * str, float x, float y, float z, int res)
{
	t_v3	pos;

	if (parse_position(&str, &pos) != res)
	{
		ck_abort_msg("res code don't match");
	}
	else if (res == 0)
	{
		ck_assert_float_eq(pos.x, x);
		ck_assert_float_eq(pos.y, y);
		ck_assert_float_eq(pos.z, z);
	}
	ck_assert(!isdigit(*str));
}

START_TEST(valid0)
{
	test("0,0,0", 0, 0, 0, 0);
	test("0.0,0.0,0.0", 0, 0, 0, 0);
	test("00.0,0,0 ", 0, 0, 0, 0);
}
END_TEST

START_TEST(valid1)
{
	test("-789.1,-0,125615.90", -789.1, 0, 125615.90, 0);
	test("+10,789.10,56	", 10, 789.10, 56, 0);
	test("+00.0,5678,01.1ABC", 0, 5678, 1.1, 0);
}
END_TEST

START_TEST(invalid0)
{
	test(" ", 0,0,0,-1);
	test(",,", 0, 0, 0, -1);
	test("...Aygsuysnui87237263762 ,", 0,0,0, -1);
}
END_TEST

START_TEST(invalid1)
{
	test("09.10,,100", 0,0,0,-1);
	test(",90.19209102,-10", 0, 0, 0, -1);
	test("90.10 3,4,5", 0,0,0, -1);
}
END_TEST

Suite	*parse_position_suite(void)
{
	Suite	*s;
	TCase	*tc_valid;
	TCase	*tc_invalid;

	s = suite_create("parse_position()");

	tc_valid = tcase_create("valid");
	tcase_add_test(tc_valid, valid0);
	tcase_add_test(tc_valid, valid1);
	suite_add_tcase(s, tc_valid);

	tc_invalid = tcase_create("invalid");
	tcase_add_test(tc_invalid, invalid0);
	tcase_add_test(tc_invalid, invalid1);
	suite_add_tcase(s, tc_invalid);

	return (s);
}
