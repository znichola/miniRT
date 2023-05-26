/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:11:41 by skoulen           #+#    #+#             */
/*   Updated: 2023/05/26 11:12:16 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	mask used to store setting to setup the app.
*/
int	getset_settings(int settings_mask)
{
	static int	set = 1;
	static int	mask = 0U;

	if (set)
	{
		mask = settings_mask;
		set = 0;
	}
	return (settings_mask & mask);
}

t_app	*getset_app(t_app *a)
{
	static t_app	*app;

	if (a)
		app = a;
	return (app);
}
