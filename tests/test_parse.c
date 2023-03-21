/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:26:31 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/21 10:17:30 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "parsing.h"

void	test(const char *file, int res)
{
	t_scene	scene;
	ck_assert_int_eq(!!parse(file, &scene), !!res);
}

START_TEST(valid0)
{
	test("files/valid1.rt", 0);
}
END_TEST

START_TEST(valid1)
{
	test("files/valid2.rt", 0);
}
END_TEST

START_TEST(syntax_error0)
{
	test("files/syntax-error0.rt", -1);
}
END_TEST

START_TEST(syntax_error1)
{
	test("files/syntax-error1.rt", -1);
}
END_TEST

START_TEST(syntax_error2)
{
	test("files/syntax-error2.rt", -1);
}
END_TEST

START_TEST(syntax_error3)
{
	test("files/syntax-error3.rt", -1);
}
END_TEST

START_TEST(parse_error0)
{
	test("files/parse-error0.rt", -1);
}
END_TEST

START_TEST(parse_error1)
{
	test("files/parse-error1.rt", -1);
}
END_TEST

START_TEST(parse_error2)
{
	test("files/parse-error2.rt", -1);
}
END_TEST

Suite	*parse_suite(void)
{
	Suite	*s;
	TCase	*tc_valid;
	TCase	*tc_syntax_error;
	TCase	*tc_parse_error;

	s = suite_create("parse()");

	tc_valid = tcase_create("valid");
	tcase_add_test(tc_valid, valid0);
	tcase_add_test(tc_valid, valid1);
	suite_add_tcase(s, tc_valid);

	tc_syntax_error = tcase_create("syntax error");
	tcase_add_test(tc_syntax_error, syntax_error0);
	tcase_add_test(tc_syntax_error, syntax_error1);
	tcase_add_test(tc_syntax_error, syntax_error2);
	tcase_add_test(tc_syntax_error, syntax_error3);
	suite_add_tcase(s, tc_syntax_error);

	tc_parse_error = tcase_create("parse error");
	tcase_add_test(tc_parse_error, parse_error0);
	tcase_add_test(tc_parse_error, parse_error1);
	tcase_add_test(tc_parse_error, parse_error2);
	suite_add_tcase(s, tc_parse_error);

	return (s);
}