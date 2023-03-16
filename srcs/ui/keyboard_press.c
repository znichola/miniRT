/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_press.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:53:08 by znichola          #+#    #+#             */
/*   Updated: 2023/03/13 17:00:12 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	keyboard_press(int key, t_app *a)
{
	if (key == e_key_esc)
		destroy_window(a);
	if (key >= 0 && key < KEYBOARD_KEY_COUNT)
	{
		a->keyboard_press[key] = 1;
	}
	return (0);
}
