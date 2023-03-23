/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_poi_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:37:42 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/23 12:16:10 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

START_TEST(basic_intersect_0)
{
	t_plane plane = {(t_v3){3,4,0}, (t_v3){0,1,1}, (t_v3){0,0,0}};
	t_v3 ray = {0,0,1};
	t_v3 source = {0,0,0};
	t_v3 poi;

	float	res = poi_plane(&plane, ray, source, &poi);

	ck_assert_float_eq_tol(res, 4, 0.01);

	//intersection should be at (0,0,4)
	ck_assert_float_eq_tol(poi.x, 0, 0.01);
	ck_assert_float_eq_tol(poi.y, 0, 0.01);
	ck_assert_float_eq_tol(poi.z, 4, 0.01);

}
END_TEST

START_TEST(basic_parallel_0)
{
	t_plane plane = {(t_v3){3,4,0}, (t_v3){0,1,1}, (t_v3){0,0,0}};
	t_v3 ray = {0,-1,1};
	t_v3 source = {0,0,0};
	t_v3 poi;

	/* the ray never touches the plane */

	float	res = poi_plane(&plane, ray, source, &poi);

	//there should be no intersection
	ck_assert_float_eq_tol(res, FLT_MAX, 0.01);

}
END_TEST

START_TEST(basic_parallel_1)
{
	t_plane plane = {(t_v3){0,0,0}, (t_v3){0,1,1}, (t_v3){0,0,0}};
	t_v3 ray = {0,-1,1};
	t_v3 source = {0,0,0};
	t_v3 poi;

	/* the ray touches the plane at an infinity of points */
	float	res = poi_plane(&plane, ray, source, &poi);

	//there should be no intersection
	ck_assert_float_eq_tol(res, FLT_MAX, 0.01);
}
END_TEST

START_TEST(origin_intersect_0)
{
	/* origin different than 0*/
	t_plane plane = {(t_v3){3,4,0}, (t_v3){0,1,1}, (t_v3){0,0,0}};
	t_v3 ray = {0,0,1};
	t_v3 source = {0,2,0};
	t_v3 poi;

	float	res = poi_plane(&plane, ray, source, &poi);

	ck_assert_float_eq_tol(res, 2, 0.01);

	//intersection should be at (0,2,2)
	ck_assert_float_eq_tol(poi.x, 0, 0.01);
	ck_assert_float_eq_tol(poi.y, 2, 0.01);
	ck_assert_float_eq_tol(poi.z, 2, 0.01);
}
END_TEST

Suite *poi_plane_suite(void)
{
	Suite *s;
	TCase *basic_intersect;
	TCase *basic_parallel;
	TCase *origin_intersect;

	s = suite_create("poi_plane()");

	basic_intersect = tcase_create("Origin zero, intersection");
	tcase_add_test(basic_intersect, basic_intersect_0);
	suite_add_tcase(s, basic_intersect);

	basic_parallel = tcase_create("Origin zero, parallel");
	tcase_add_test(basic_parallel, basic_parallel_0);
	tcase_add_test(basic_parallel, basic_parallel_1);
	suite_add_tcase(s, basic_parallel);

	origin_intersect = tcase_create("Origin different than zero, intersection");
	tcase_add_test(origin_intersect, origin_intersect_0);
	suite_add_tcase(s, origin_intersect);

	return (s);
}