/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:35:01 by skoulen           #+#    #+#             */
/*   Updated: 2023/03/16 16:08:54 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdio.h>
# include <ctype.h>
# include "minirt.h"
# include "check.h"

Suite	*parse_float_suite(void);
Suite	*parse_position_suite(void);
Suite	*parse_color_suite(void);

#endif