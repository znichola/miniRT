/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:04:20 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/16 16:29:09 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "parsing.h"

static void	test(const char *str, float r, float g, float b, int res)
{
	t_v3	clr;

	if (parse_position(&str, &clr) != res)
	{
		ck_abort_msg("res code don't match");
	}
	else if (res == 0)
	{
		ck_assert_float_eq(clr.x, r);
		ck_assert_float_eq(clr.y, g);
		ck_assert_float_eq(clr.z, b);
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

Suite	*parse_color_suite(void)
{
	Suite	*s;
	TCase	*tc_valid;
	//TCase	*tc_invalid;

	s = suite_create("parse_color()");

	tc_valid = tcase_create("valid");
	tcase_add_test(tc_valid, valid0);
	suite_add_tcase(s, tc_valid);

	/*tc_invalid = tcase_create("invalid");
	tcase_add_test(tc_invalid, invalid0);
	tcase_add_test(tc_invalid, invalid1);
	suite_add_tcase(s, tc_invalid);*/

	return (s);
}