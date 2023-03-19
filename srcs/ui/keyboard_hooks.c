/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:53:08 by znichola          #+#    #+#             */
/*   Updated: 2023/03/19 12:23:06 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	keyboard_on_press(int key, t_app *a)
{
	// printf("pressed! %d\n", key);
	if (key == e_key_esc)
		destroy_window(a);
	if (key >= 0 && key < KEYBOARD_KEY_COUNT)
	{
		a->keyboard_press[key] = 1;
		a->keyboard_held[key] = 1;
	}
	return (0);
}

int	keyboard_on_release(int key, t_app *a)
{
	// printf("released! %d\n", key);
	if (key >= 0 && key < KEYBOARD_KEY_COUNT)
	{
		a->keyboard_release[key] = 1;
		a->keyboard_held[key] = 0;
	}
	return (0);
}
