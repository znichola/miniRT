/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_poi_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:28:38 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/22 23:50:04 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

START_TEST(basic_intersect0)
{
	t_sphere sp = {.position=(t_v3){0,0,5}, .radius=1.0, .colour= (t_v3){0,0,0}};
	t_v3 poi = {-1,-1, -1};
	t_v3 origin = {0,0,0};
	t_v3 ray = {0,0,1};
	float	res = poi_sphere(&sp, ray, origin, &poi);

	ck_assert_float_eq_tol(res, 1, 0.0005); //there should be an intersection

	//poi should be {0,0,4}
	ck_assert_float_eq(poi.x, 0);
	ck_assert_float_eq(poi.y, 0);
	ck_assert_float_eq(poi.z, 4);
}
END_TEST

START_TEST(basic_nointersect0)
{
	t_sphere sp = {.position=(t_v3){0,5,5}, .radius=1.0, .colour= (t_v3){0,0,0}};
	t_v3 poi = {-1,-1, -1};
	t_v3 origin = {0,0,0};
	t_v3 ray = {0,0,1};
	float	res = poi_sphere(&sp, ray, origin, &poi);

	ck_assert_float_eq_tol(res, FLT_MAX, 0.0005); //there should be no intersection
}
END_TEST

START_TEST(basic_intersect1)
{
	t_sphere sp = {.position=(t_v3){0,5,5}, .radius=1.0, .colour= (t_v3){0,0,0}};
	t_v3 poi = {-1,-1, -1};
	t_v3 origin = {0,0,0};
	t_v3 ray = {0,1,1};
	float	res = poi_sphere(&sp, ray, origin, &poi);

	ck_assert_float_eq_tol(res, 1, 0.0005); //there should be an intersection

	//poi should be {0,4.29,4.29}
	ck_assert_float_eq_tol(poi.x, 0, 0.01);
	ck_assert_float_eq_tol(poi.y, 4.29, 0.01);
	ck_assert_float_eq_tol(poi.z, 4.29, 0.01);
}
END_TEST

START_TEST(origin_intersect0) // origin different than 0 0 0
{
	t_sphere sp = {.position=(t_v3){0,5,5}, .radius=1.0, .colour= (t_v3){0,0,0}};
	t_v3 poi = {-1,-1, -1};
	t_v3 origin = {0,1,0};
	t_v3 ray = {0,1,1};
	float	res = poi_sphere(&sp, ray, origin, &poi);

	ck_assert_float_eq_tol(res, 1, 0.0005); //there should be an intersection

	//poi should be {0,5,4}
	ck_assert_float_eq_tol(poi.x, 0, 0.01);
	ck_assert_float_eq_tol(poi.y, 5, 0.01);
	ck_assert_float_eq_tol(poi.z, 4, 0.01);
}
END_TEST

START_TEST(origin_nointersect0) // origin different than 0 0 0
{
	t_sphere sp = {.position=(t_v3){0,5,5}, .radius=1.0, .colour= (t_v3){0,0,0}};
	t_v3 poi = {-1,-1, -1};
	t_v3 origin = {2,1,-3};
	t_v3 ray = {0,1,1};
	float	res = poi_sphere(&sp, ray, origin, &poi);

	ck_assert_float_eq_tol(res, FLT_MAX, 0.0005); //there should no intersection
}
END_TEST

START_TEST(origin_intersect1) // origin different than 0 0 0
{
	t_sphere sp = {.position=(t_v3){2,8,5}, .radius=1.0, .colour= (t_v3){0,0,0}};
	t_v3 poi = {-1,-1, -1};
	t_v3 origin = {2,1,-3};
	t_v3 ray = {0,1,1};
	float	res = poi_sphere(&sp, ray, origin, &poi);

	ck_assert_float_eq_tol(res, 1, 0.0005); //there should be an intersection

	//poi should be {2,8,4}
	ck_assert_float_eq_tol(poi.x, 2, 0.01);
	ck_assert_float_eq_tol(poi.y, 8, 0.01);
	ck_assert_float_eq_tol(poi.z, 4, 0.01);
}
END_TEST

/* testing what happens when the source is in the sphere */
START_TEST(inside_0) // origin different than 0 0 0
{
	t_sphere sp = {.position=(t_v3){0,0,0}, .radius=5.0, .colour= (t_v3){0,0,0}};
	t_v3 poi = {-1,-1, -1};
	t_v3 origin = {0,0,0};
	t_v3 ray = {0,0,1};
	float	res = poi_sphere(&sp, ray, origin, &poi);

	ck_assert_float_eq_tol(res, 1, 0.0005); //there should be an intersection

	//poi should be {0,0, 5}
	ck_assert_float_eq_tol(poi.x, 0, 0.01);
	ck_assert_float_eq_tol(poi.y, 0, 0.01);
	ck_assert_float_eq_tol(poi.z, 5, 0.01);
}
END_TEST

/* testing what happens when the source is in the sphere */
START_TEST(inside_1) // origin different than 0 0 0
{
	t_sphere sp = {.position=(t_v3){0,-1,2}, .radius=5.0, .colour= (t_v3){0,0,0}};
	t_v3 poi = {-1,-1, -1};
	t_v3 origin = {0,0,0};
	t_v3 ray = {0,0,1};
	float	res = poi_sphere(&sp, ray, origin, &poi);

	ck_assert_float_eq_tol(res, 1, 0.0005); //there should be an intersection

	//poi should be {0,0,6.9}
	ck_assert_float_eq_tol(poi.x, 0, 0.01);
	ck_assert_float_eq_tol(poi.y, 0, 0.01);
	ck_assert_float_eq_tol(poi.z, 6.9, 0.01);
}
END_TEST

/* testing what happens when the source is in the sphere */
START_TEST(inside_2) // origin different than 0 0 0
{
	t_sphere sp = {.position=(t_v3){0,0,-2}, .radius=5.0, .colour= (t_v3){0,0,0}};
	t_v3 poi = {-1,-1, -1};
	t_v3 origin = {0,0,0};
	t_v3 ray = {0,0,1};
	float	res = poi_sphere(&sp, ray, origin, &poi);

	ck_assert_float_eq_tol(res, 1, 0.0005); //there should be an intersection

	//poi should be {0,0,3}
	ck_assert_float_eq_tol(poi.x, 0, 0.01);
	ck_assert_float_eq_tol(poi.y, 0, 0.01);
	ck_assert_float_eq_tol(poi.z, 3, 0.01);
}
END_TEST

START_TEST(on_the_origin_0)
{
	t_sphere sp = {.position=(t_v3){0,0,5}, .radius=5.0, .colour= (t_v3){0,0,0}};
	t_v3 poi = {-1,-1, -1};
	t_v3 origin = {0,0,0};
	t_v3 ray = {0,0,1};
	float	res = poi_sphere(&sp, ray, origin, &poi);

	ck_assert_float_eq_tol(res, 1, 0.0005); //there should be an intersection

	//poi should be {0,0,3}
	ck_assert_float_eq_tol(poi.x, 0, 0.01);
	ck_assert_float_eq_tol(poi.y, 0, 0.01);
	ck_assert_float_eq_tol(poi.z, 0, 0.01);
}
END_TEST

Suite *poi_sphere_suite(void)
{
	Suite	*s;
	TCase	*basic_intersect;
	TCase	*basic_nointersect;
	TCase	*origin_intersect;
	TCase	*origin_nointersect;
	TCase	*inside;
	TCase	*on_the_origin;

	s = suite_create("poi_sphere()");

	basic_intersect = tcase_create("basic with intersection");
	tcase_add_test(basic_intersect, basic_intersect0);
	tcase_add_test(basic_intersect, basic_intersect1);
	suite_add_tcase(s, basic_intersect);

	basic_nointersect = tcase_create("basic with no intersection");
	tcase_add_test(basic_nointersect, basic_nointersect0);
	suite_add_tcase(s, basic_nointersect);

	origin_intersect = tcase_create("origin not zero, intersection");
	tcase_add_test(origin_intersect, origin_intersect0);
	tcase_add_test(origin_intersect, origin_intersect1);
	suite_add_tcase(s, origin_intersect);

	origin_nointersect = tcase_create("origin not zero, no intersection");
	tcase_add_test(origin_nointersect, origin_nointersect0);
	suite_add_tcase(s, origin_nointersect);

	inside = tcase_create("Origin is inside the sphere");
	tcase_add_test(inside, inside_0);
	tcase_add_test(inside, inside_1);
	tcase_add_test(inside, inside_2);
	suite_add_tcase(s, inside);

	on_the_origin = tcase_create("Intersection point is on the origin");
	tcase_add_test(inside, on_the_origin_0);
	suite_add_tcase(s, on_the_origin);

	return (s);
}
