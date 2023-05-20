/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   un_connected_tests.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:46:45 by znichola          #+#    #+#             */
/*   Updated: 2023/05/21 00:10:36 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	tests(void)
{
	{
	printf("testing the determinant\n");

	t_t2 td;

	td.m[0][0] = 1;
	td.m[0][1] = 5;
	td.m[1][0] = -3;
	td.m[1][1] = 2;
	printf("determinant 17    : %.1f\n", t2_determinant(td));
	}
	{
	printf("testing the sub t_t3\n");

	t_t3 t3;

	t3.m[0][0] = 1;
	t3.m[0][1] = 5;
	t3.m[0][2] = 0;

	t3.m[1][0] = -3;
	t3.m[1][1] = 2;
	t3.m[1][2] = 7;

	t3.m[2][0] = 0;
	t3.m[2][1] = 6;
	t3.m[2][2] = 3;

	t_t2 r3 = t3_submatrix(t3, 0, 2);

	for (int i = 0; i < 2; i++)
		printf("|%.1f %.1f|\n", r3.m[i][0], r3.m[i][1]);
	}
	{
	printf("testing the sub t_t3\n");

	t_t4 t4;

	t4.m[0][0] = 6;
	t4.m[0][1] = 1;
	t4.m[0][2] = 1;
	t4.m[0][3] = 6;

	t4.m[1][0] = -8;
	t4.m[1][1] = 5;
	t4.m[1][2] = 8;
	t4.m[1][3] = 6;

	t4.m[2][0] = -1;
	t4.m[2][1] = 0;
	t4.m[2][2] = 8;
	t4.m[2][3] = 2;

	t4.m[3][0] = -7;
	t4.m[3][1] = 1;
	t4.m[3][2] = -1;
	t4.m[3][3] = 1;

	t_t3 r4 = t4_submatrix(t4, 2, 1);

	for (int i = 0; i < 3; i++)
		printf("|%.1f %.1f %.1f|\n", r4.m[i][0], r4.m[i][1], r4.m[i][2]);
	}
	{
	printf("testing the minor\n");

	t_t3 tm;

	tm.m[0][0] = 3;
	tm.m[0][1] = 5;
	tm.m[0][2] = 0;

	tm.m[1][0] = 5;
	tm.m[1][1] = -1;
	tm.m[1][2] = -7;

	tm.m[2][0] = 6;
	tm.m[2][1] = -1;
	tm.m[2][2] = 5;

	printf("minor 25      : %.1f\n", t3_minor(tm, 1, 0));

	printf("testing the cofactor\n");

	printf("minor -12     : %.1f\n", t3_minor(tm, 0, 0));
	printf("cofactor -12  : %.1f\n", t3_cofactor(tm, 0, 0));
	printf("minor 25      : %.1f\n", t3_minor(tm, 1, 0));
	printf("cofactor -25  : %.1f\n", t3_cofactor(tm, 1, 0));
	}
	{
	printf("testing 3x3 determinant\n");
	t_t3 t;

	t.m[0][0] = 1;
	t.m[0][1] = 2;
	t.m[0][2] = 6;

	t.m[1][0] = -5;
	t.m[1][1] = 8;
	t.m[1][2] = -4;

	t.m[2][0] = 2;
	t.m[2][1] = 6;
	t.m[2][2] = 4;

	printf("cofactor    56  : %.1f\n", t3_cofactor(t, 0, 0));
	printf("cofactor    12  : %.1f\n", t3_cofactor(t, 0, 1));
	printf("cofactor   -46  : %.1f\n", t3_cofactor(t, 0, 2));
	printf("determiant -196 : %.1f\n", t3_determinant(t));
	}
	{
	printf("testing 4x4 determinant\n");
	t_t4 t;

	t.m[0][0] = -2;
	t.m[0][1] = -8;
	t.m[0][2] = 3;
	t.m[0][3] = 5;

	t.m[1][0] = -3;
	t.m[1][1] = 1;
	t.m[1][2] = 7;
	t.m[1][3] = 3;

	t.m[2][0] = 1;
	t.m[2][1] = 2;
	t.m[2][2] = -9;
	t.m[2][3] = 6;

	t.m[3][0] = -6;
	t.m[3][1] = 7;
	t.m[3][2] = 7;
	t.m[3][3] = -9;

	printf("cofactor    690  : %.1f\n", t4_cofactor(t, 0, 0));
	printf("cofactor    447  : %.1f\n", t4_cofactor(t, 0, 1));
	printf("cofactor    210  : %.1f\n", t4_cofactor(t, 0, 2));
	printf("cofactor    51   : %.1f\n", t4_cofactor(t, 0, 3));
	printf("determiant -4071 : %.1f\n", t4_determinant(t));
	}
	{
	printf("testing 4x4 determinant\n");
	t_t4 t;

	t.m[0][0] = -2;
	t.m[0][1] = -8;
	t.m[0][2] = 3;
	t.m[0][3] = 5;

	t.m[1][0] = -3;
	t.m[1][1] = 1;
	t.m[1][2] = 7;
	t.m[1][3] = 3;

	t.m[2][0] = 1;
	t.m[2][1] = 2;
	t.m[2][2] = -9;
	t.m[2][3] = 6;

	t.m[3][0] = -6;
	t.m[3][1] = 7;
	t.m[3][2] = 7;
	t.m[3][3] = -9;

	printf("cofactor    690  : %.1f\n", t4_cofactor(t, 0, 0));
	printf("cofactor    447  : %.1f\n", t4_cofactor(t, 0, 1));
	printf("cofactor    210  : %.1f\n", t4_cofactor(t, 0, 2));
	printf("cofactor    51   : %.1f\n", t4_cofactor(t, 0, 3));
	printf("determiant -4071 : %.1f\n", t4_determinant(t));
	}
	{
	printf("testing 4x4 invertability\n");
	t_t4 t;

	t.m[0][0] = 6;
	t.m[0][1] = 4;
	t.m[0][2] = 4;
	t.m[0][3] = 4;

	t.m[1][0] = 5;
	t.m[1][1] = 5;
	t.m[1][2] = 7;
	t.m[1][3] = 6;

	t.m[2][0] = 4;
	t.m[2][1] = -9;
	t.m[2][2] = 3;
	t.m[2][3] = -7;

	t.m[3][0] = 9;
	t.m[3][1] = 1;
	t.m[3][2] = 7;
	t.m[3][3] = -6;

	printf("invertability 1 : %d\n", t4_is_invertable(t));
	}
	{
	t_t4 t;

	t.m[0][0] = -4;
	t.m[0][1] = 2;
	t.m[0][2] = -2;
	t.m[0][3] = -3;

	t.m[1][0] = 9;
	t.m[1][1] = 6;
	t.m[1][2] = 2;
	t.m[1][3] = 6;

	t.m[2][0] = 0;
	t.m[2][1] = -5;
	t.m[2][2] = 1;
	t.m[2][3] = -5;

	t.m[3][0] = 0;
	t.m[3][1] = 0;
	t.m[3][2] = 0;
	t.m[3][3] = 0;

	printf("invertability 0 : %d\n", t4_is_invertable(t));
	}
	{
	t_t4 t;

	t.m[0][0] = -5;
	t.m[0][1] = 2;
	t.m[0][2] = 6;
	t.m[0][3] = -8;

	t.m[1][0] = 1;
	t.m[1][1] = -5;
	t.m[1][2] = 1;
	t.m[1][3] = 8;

	t.m[2][0] = 7;
	t.m[2][1] = 7;
	t.m[2][2] = -6;
	t.m[2][3] = -7;

	t.m[3][0] = 1;
	t.m[3][1] = -3;
	t.m[3][2] = 7;
	t.m[3][3] = 4;

	t_t4 inverse = t4_inverse(t);
	printf("determinant 532 : %.1f\n", t4_determinant(t));
	printf("cofactor   -160 : %.1f\n", t4_cofactor(t, 2, 3));
	printf("inverse    %.1f : %.1f\n", -160/532.0f, inverse.m[3][2]);
	printf("cofactor    105 : %.1f\n", t4_cofactor(t, 3, 2));
	printf("inverse    %4.1f : %.1f\n", 105/532.0f, inverse.m[2][3]);
	for (int i = 0; i < 4; i++)
		printf("|%6.3f %6.3f %6.3f %6.3f|\n", inverse.m[i][0], inverse.m[i][1], inverse.m[i][2], inverse.m[i][3]);
	// check the book to compare results, but looks good to me!!!
	}
	exit(-42);
}

void	tests(t_app *a)
{
	{
		printf("Camera transformation\n");
		// 200 * 125 at pi/2
		t_camera *c = &a->s.camera;
		printf("fov         %.4f\n", c->fov);
		printf("half_width  %.1f\n", c->half_width);
		printf("half_height %.1f\n", c->half_height);
		printf("pix size 0.01 : %.4f\n", c->pixel_size);
	}
	{
		t_v3	from = (t_v3){0, 0, 8};
		t_v3	to = (t_v3){0, 0, 0};
		t_v3	up = (t_v3){0, 1, 0};
		t_m4	m = view_transform(from, to, up);
		t_m4	t = translation(0, 0, -8);

		printf("View Transformation\n");
		print_m4(m);
		printf("\n");
		print_m4(t);
	}
	{
		t_v3	from = (t_v3){1, 3, 2};
		t_v3	to = (t_v3){4, -2, 8};
		t_v3	up = (t_v3){1, 1, 0};
		t_m4	m = view_transform(from, to, up);

		printf("View Transformation\n");
		print_m4(m);
	}
	exit(42);
}
