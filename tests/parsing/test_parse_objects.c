/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:13:12 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/22 16:04:25 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "minirt_structs.h"
#include <math.h>

static void	test_ambiant(const char *str, float ratio, t_v3 clr, int res)
{
	t_ambiant	a;

	if (!!parse_ambiant(&str, &a) != !!res)
		ck_abort_msg("res codes don't match");
	if (res == 0)
	{
		ck_assert_float_eq(a.ratio, ratio);
		ck_assert_float_eq(a.colour.x, clr.x);
		ck_assert_float_eq(a.colour.y, clr.y);
		ck_assert_float_eq(a.colour.z, clr.z);
		ck_assert(*str == '\0');
	}
}

static void	test_camera(const char *str, t_v3 pos, t_v3 ori, int fov, int res)
{
	t_camera	c;

	if (!!parse_camera(&str, &c) != !!res)
		ck_abort_msg("res codes don't match");
	if (res == 0)
	{
		ck_assert_float_eq(c.position.x, pos.x);
		ck_assert_float_eq(c.position.y, pos.y);
		ck_assert_float_eq(c.position.z, pos.z);

		ori = v3_unitvec(ori);
		ck_assert_float_eq(c.orientation.x, ori.x);
		ck_assert_float_eq(c.orientation.y, ori.y);
		ck_assert_float_eq(c.orientation.z, ori.z);

		ck_assert_float_eq(c.fov, (float)fov * M_PI / 180);
		ck_assert(*str == '\0');
	}
}

static void	test_light(const char *str, t_v3 pos, float ratio, t_v3 clr, int res)
{
	t_light	l;

	if (!!parse_light(&str, &l) != !!res)
		ck_abort_msg("res codes don't match");
	if (res == 0)
	{
		ck_assert_float_eq(l.position.x, pos.x);
		ck_assert_float_eq(l.position.y, pos.y);
		ck_assert_float_eq(l.position.z, pos.z);

		ck_assert_float_eq(l.ratio, ratio);

		ck_assert_float_eq(l.colour.x, clr.x);
		ck_assert_float_eq(l.colour.y, clr.y);
		ck_assert_float_eq(l.colour.z, clr.z);

		ck_assert(*str == '\0');
	}
}

static void	test_sphere(const char *str, t_v3 pos, float diam, t_v3 clr, int res)
{
	t_sphere	sp;

	if (!!parse_sphere(&str, &sp) != !!res)
		ck_abort_msg("res codes don't match");
	if (res == 0)
	{
		ck_assert_float_eq_tol(sp.position.x, pos.x, 0.01);
		ck_assert_float_eq(sp.position.y, pos.y);
		ck_assert_float_eq(sp.position.z, pos.z);

		ck_assert_float_eq(sp.radius * 2, diam);

		ck_assert_float_eq(sp.colour.x, clr.x);
		ck_assert_float_eq(sp.colour.y, clr.y);
		ck_assert_float_eq(sp.colour.z, clr.z);

		ck_assert(*str == '\0');
	}
}

static void	test_plane(const char *str, t_v3 pos, t_v3 ori, t_v3 clr, int res)
{
	t_plane	pl;

	if (!!parse_plane(&str, &pl) != !!res)
		ck_abort_msg("res codes don't match");
	if (res == 0)
	{
		ck_assert_float_eq(pl.position.x, pos.x);
		ck_assert_float_eq(pl.position.y, pos.y);
		ck_assert_float_eq(pl.position.z, pos.z);

		ori = v3_unitvec(ori);
		ck_assert_float_eq(pl.orientation.x, ori.x);
		ck_assert_float_eq(pl.orientation.y, ori.y);
		ck_assert_float_eq(pl.orientation.z, ori.z);

		ck_assert_float_eq(pl.colour.x, clr.x);
		ck_assert_float_eq(pl.colour.y, clr.y);
		ck_assert_float_eq(pl.colour.z, clr.z);

		ck_assert(*str == '\0');
	}
}

static void	test_cylinder(const char *str, t_v3 pos, t_v3 ori, float diam, float height, t_v3 clr, int res)
{
	t_cylinder	cy;

	if (!!parse_cylinder(&str, &cy) != !!res)
		ck_abort_msg("res codes don't match");
	if (res == 0)
	{
		ck_assert_float_eq(cy.position.x, pos.x);
		ck_assert_float_eq(cy.position.y, pos.y);
		ck_assert_float_eq(cy.position.z, pos.z);

		ori = v3_unitvec(ori);
		ck_assert_float_eq(cy.orientation.x, ori.x);
		ck_assert_float_eq(cy.orientation.y, ori.y);
		ck_assert_float_eq(cy.orientation.z, ori.z);

		ck_assert_float_eq(cy.radius * 2, diam);
		ck_assert_float_eq(cy.height, height);

		ck_assert_float_eq(cy.colour.x, clr.x);
		ck_assert_float_eq(cy.colour.y, clr.y);
		ck_assert_float_eq(cy.colour.z, clr.z);

		ck_assert(*str == '\0');
	}
}

/* tests for parsing the ambiant object */

START_TEST(a_valid0)
{
	test_ambiant(" 0.2 255,255,255", 0.2, (t_v3){1,1,1}, 0);
}
END_TEST

START_TEST(a_valid1)
{
	test_ambiant("1    0,127,255     ", 1.0, (t_v3){0,(float)127/255,1}, 0);
}
END_TEST

START_TEST(a_invalid0)
{
	test_ambiant("-1 0,0,0", 0, (t_v3){0,0,0}, -1);
}
END_TEST

START_TEST(a_invalid1)
{
	test_ambiant("0.5		80,80,-13", 0, (t_v3){0,0,0}, -1);
}
END_TEST

START_TEST(a_invalid2)
{
	test_ambiant("  0.8 0,0,0 ABC", 0, (t_v3){0,0,0}, -1);
	test_ambiant("yuygsuqgys 0.9m 130,130,130", 0, (t_v3){0,0,0}, -1);
	test_ambiant("0.8 ABC 45,45,45", 0, (t_v3){0,0,0}, -1);
	test_ambiant("0.5+80,80,-13", 0, (t_v3){0,0,0}, -1);
}
END_TEST

/* tests for parsing the camera object */

START_TEST(c_valid0)
{
	test_camera(" -50.0,0,20 0,0,1 70", (t_v3){-50,0,20}, (t_v3){0,0,1}, 70, 0);
}
END_TEST

START_TEST(c_valid1)
{
	test_camera("0.03,23456624,20.4 -1.0,0.6,1.0 180   ",
		(t_v3){0.03,23456624,20.4}, (t_v3){-1,0.6,1}, 180, 0);
}
END_TEST

/*
	we have decided orientation doesn't have to be a unit vector,
	we unify it ourselves
*/
START_TEST(c_valid2)
{
	test_camera("0.03,23456624,20.4 -1.0,35.6,1.0 180   ",
		(t_v3){0.03,23456624,20.4}, (t_v3){-1,35.6,1}, 180, 0);
}
END_TEST

/* orientation cannot bu nul */
START_TEST(c_invalid0)
{
	test_camera("0,0,0   0,0,0   30",
	(t_v3){0,0,0}, (t_v3){0,0,0}, 0, -1);
}
END_TEST

START_TEST(c_invalid1)
{
	test_camera("10,10,10 0.5,0,0, 181",
		(t_v3){0,0,0}, (t_v3){0,0,0}, 0, -1);
	test_camera("10,10,10 0.5,0,0, -1",
		(t_v3){0,0,0}, (t_v3){0,0,0}, 0, -1);
}
END_TEST

START_TEST(c_invalid2)
{
	test_camera("10,10,10 -1.2,0,0, 30ABC",
		(t_v3){0,0,0}, (t_v3){0,0,0}, 0, -1);
	test_camera("10,10,10 1876-1.2,0,0, 30",
		(t_v3){0,0,0}, (t_v3){0,0,0}, 0, -1);
	test_camera("10,10,10 -1.2,0,0,30",
		(t_v3){0,0,0}, (t_v3){0,0,0}, 0, -1);
	test_camera("10,10,10-1.2,0,0, 30",
		(t_v3){0,0,0}, (t_v3){0,0,0}, 0, -1);
}
END_TEST

/* tests for parsing the light object */

START_TEST(l_valid0)
{
	test_light("-40.0,50.0,0.0 0.6 10,0,255",
		(t_v3){-40, 50, 0}, 0.6, (t_v3){(float)10/255, (float)0/255, (float)255/255}, 0);
}
END_TEST

START_TEST(l_valid1)
{
	test_light("    0,0,1000 0.0		0,0,67",
		(t_v3){0, 0, 1000}, 0.0, (t_v3){(float)0/255, (float)0/255, (float)67/255}, 0);
}
END_TEST

START_TEST(l_invalid0)
{
	test_light("",
		(t_v3){0,0,0}, 0, (t_v3){0,0,0}, -1);
	test_light("7,6,8 1 0,0,",
		(t_v3){0,0,0}, 0, (t_v3){0,0,0}, -1);
	test_light("01234557981298901819289182901821726716278162",
		(t_v3){0,0,0}, 0, (t_v3){0,0,0}, -1);

}
END_TEST

START_TEST(l_invalid1)
{
	test_light(" 45.56.89, 0.01, 10,0,255",
		(t_v3){0,0,0}, 0, (t_v3){0,0,0}, -1);
	test_light("78.0,-!10,78  0.01 10,0,255",
		(t_v3){0,0,0}, 0, (t_v3){0,0,0}, -1);
}
END_TEST

/* tests sphere*/

START_TEST(sp_valid0)
{
	test_sphere("0.0,0.0,20.6 	12.6  10,0,255",
		(t_v3){0,0,20.6}, 12.6, (t_v3){(float)10/255,0,1}, 0);
}
END_TEST

START_TEST(sp_valid1)
{
	test_sphere("1.236,-456,0.00 20000 0,0,0",
		(t_v3){ 1.236, -456, 0}, 20000, (t_v3){0,0,0}, 0);
}
END_TEST

START_TEST(sp_invalid0) //negative diameter
{
	test_sphere("0,0,0 -12.67, 0,0,0    ",
		(t_v3){0,0,0}, 0, (t_v3){0,0,0}, -1);

	test_sphere("0,0,0 0 0,0,0    ",
		(t_v3){0,0,0}, 0, (t_v3){0,0,0}, -1);
}
END_TEST

/* tests plane */
START_TEST(pl_valid0)
{
	test_plane("0.0,0.0,-10.0 0.0,1.0,0.0 0,0,255",
		(t_v3){0,0,0}, (t_v3){0,1,0}, (t_v3){0,0,255}, 0);
}
END_TEST

START_TEST(pl_valid1)
{
	test_plane("34.567,678,0.12    	 -1,-0.5,+0.9 255,255,255   ",
		(t_v3){34.567, 678, 0.12}, (t_v3){-1, -0.5, 0.9}, (t_v3){255,255,255}, 0);
}
END_TEST

START_TEST(pl_invalid0)
{
	test_plane("0,0,0,0,0,0,0,0,00,0,00,0,0,0,0,0,00,0,00,0,0,0,0,0,0",
		(t_v3){0,0,0}, (t_v3){0,0,0}, (t_v3){0,0,0}, -1);
	test_plane("0.1.3.4.5.6.6",
		(t_v3){0,0,0}, (t_v3){0,0,0}, (t_v3){0,0,0}, -1);
	test_plane(" ABGW GUWY OIND YW NUYDOUNWI UGGDNUWD 616112398 139 010-1kxo1i3 ",
		(t_v3){0,0,0}, (t_v3){0,0,0}, (t_v3){0,0,0}, -1);
}
END_TEST

START_TEST(pl_invalid1)
{
	test_plane("100.30,40,0.56    0,0,1 0,256,0   ",
		(t_v3){0,0,0}, (t_v3){0,0,0}, (t_v3){0,0,0}, -1);
}
END_TEST

START_TEST(pl_invalid2)
{
	test_plane("100.30,40,8      0,0,0   0,0,0",
	(t_v3){0,0,0}, (t_v3){0,0,0}, (t_v3){0,0,0}, -1);
}
END_TEST
/* tests cylinder */

START_TEST(cy_valid0)
{
	test_cylinder("50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255",
		(t_v3){50,0,20.6}, (t_v3){0,0,1}, 14.2, 21.42, (t_v3){(float)10/255,0,1}, 0);

	test_cylinder("89.01,34,0 -1.0,0.5,1.0 135 21.42 10,0,33",
		(t_v3){89.01,34,0}, (t_v3){-1,0.5,1}, 135, 21.42, (t_v3){(float)10/255,0,(float)33/255}, 0);
}
END_TEST

START_TEST(cy_invalid0)
{
	test_cylinder("50.0,0.0,20.6 0.0,0.0,1.0 -14.2, 21.42 10,0,255",
		(t_v3){50,0,20.6}, (t_v3){0,0,1}, 14.2, 21.42, (t_v3){(float)10/255,0,1}, -1);

	test_cylinder("50.0,0.0,20.6 0.0,0.0,1.0 14.2, 0 10,0,255",
		(t_v3){50,0,20.6}, (t_v3){0,0,1}, 14.2, 21.42, (t_v3){(float)10/255,0,1}, -1);

	test_cylinder("50.0,0.0,20.6 0.0,0.0,1.0 14.2, 21.42 10,0,-255",
		(t_v3){50,0,20.6}, (t_v3){0,0,1}, 14.2, 21.42, (t_v3){(float)10/255,0,1}, -1);
}
END_TEST

Suite	*parse_objects_suite(void)
{
	Suite	*s;
	TCase	*tc_ambiant_valid;
	TCase	*tc_ambiant_invalid;
	TCase	*tc_camera_valid;
	TCase	*tc_camera_invalid;
	TCase	*tc_light_valid;
	TCase	*tc_light_invalid;
	TCase	*tc_sphere_valid;
	TCase	*tc_sphere_invalid;
	TCase	*tc_plane_valid;
	TCase	*tc_plane_invalid;
	TCase	*tc_cylinder_valid;
	TCase	*tc_cylinder_invalid;

	s = suite_create("parse objects");

	tc_ambiant_valid = tcase_create("ambiant: valid");
	tcase_add_test(tc_ambiant_valid, a_valid0);
	tcase_add_test(tc_ambiant_valid, a_valid1);
	suite_add_tcase(s, tc_ambiant_valid);

	tc_ambiant_invalid = tcase_create("ambiant: invalid");
	tcase_add_test(tc_ambiant_invalid, a_invalid0);
	tcase_add_test(tc_ambiant_invalid, a_invalid1);
	tcase_add_test(tc_ambiant_invalid, a_invalid2);
	suite_add_tcase(s, tc_ambiant_invalid);

	tc_camera_valid = tcase_create("camera: valid");
	tcase_add_test(tc_camera_valid, c_valid0);
	tcase_add_test(tc_camera_valid, c_valid1);
	tcase_add_test(tc_camera_valid, c_valid2);
	suite_add_tcase(s, tc_camera_valid);

	tc_camera_invalid = tcase_create("camera: invalid");
	tcase_add_test(tc_camera_invalid, c_invalid0);
	tcase_add_test(tc_camera_invalid, c_invalid1);
	tcase_add_test(tc_camera_invalid, c_invalid2);
	suite_add_tcase(s, tc_camera_invalid);

	tc_light_valid = tcase_create("light: valid");
	tcase_add_test(tc_light_valid, l_valid0);
	tcase_add_test(tc_light_valid, l_valid1);
	suite_add_tcase(s, tc_light_valid);

	tc_light_invalid = tcase_create("light: invalid");
	tcase_add_test(tc_light_invalid, l_invalid0);
	tcase_add_test(tc_light_invalid, l_invalid1);
	suite_add_tcase(s, tc_light_invalid);

	tc_sphere_valid = tcase_create("sphere: valid");
	tcase_add_test(tc_sphere_valid, sp_valid0);
	tcase_add_test(tc_sphere_valid, sp_valid1);
	suite_add_tcase(s, tc_sphere_valid);

	tc_sphere_invalid = tcase_create("sphere: invalid");
	tcase_add_test(tc_sphere_invalid, sp_invalid0);
	suite_add_tcase(s, tc_sphere_invalid);

	tc_plane_valid = tcase_create("plane: valid");
	tcase_add_test(tc_plane_valid, pl_valid0);
	tcase_add_test(tc_plane_valid, pl_valid1);
	suite_add_tcase(s, tc_sphere_valid);

	tc_plane_invalid = tcase_create("plane: invalid");
	tcase_add_test(tc_plane_invalid, pl_invalid0);
	tcase_add_test(tc_plane_invalid, pl_invalid1);
	tcase_add_test(tc_plane_invalid, pl_invalid2);
	suite_add_tcase(s, tc_plane_invalid);

	tc_cylinder_valid = tcase_create("cylinder: valid");
	tcase_add_test(tc_cylinder_valid, cy_valid0);
	suite_add_tcase(s, tc_cylinder_valid);

	tc_cylinder_invalid = tcase_create("cylinder: invalid");
	tcase_add_test(tc_cylinder_invalid, cy_invalid0);
	suite_add_tcase(s, tc_cylinder_invalid);

	return (s);
}