/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_printer.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:05:04 by znichola          #+#    #+#             */
/*   Updated: 2023/05/20 23:33:24 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	this is just to print the code needed for the matrix multiplication,
	it will soon become apparent why this is a nessary step when faced
	with the sheer number of characters involved.

	00 01 02 03
	10 11 12 13
	20 21 22 23
	30 31 32 33

	a * b = c
	a.ti0 * b.t0j + a.ti1 * b.t1j + a.ti2 * b.tj2 + a.ti3 * b.tj3, // cij

	and the matrix data structure is:
*/
typedef struct	s_m4
{
	float t00;
	float t01;
	float t02;
	float t03;

	float t10;
	float t11;
	float t12;
	float t13;

	float t20;
	float t21;
	float t22;
	float t23;

	float t30;
	float t31;
	float t32;
	float t33;
}	t_m4;


#include <string>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

int main(void)
{
	std::string s("a.ti0 * b.t0j + a.ti1 * b.t1j + a.ti2 * b.t2j + a.ti3 * b.t3j, //cij");
	// std::string s("t.m[i][j] = m->tij;");
	// std::string s("m.tij = t.m[i][j];");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::string line(s);
			std::replace(line.begin(), line.end(), 'i', char(i+48));
			std::replace(line.begin(), line.end(), 'j', char(j+48));
			std::cout << line << std::endl;
		}
	}
}
