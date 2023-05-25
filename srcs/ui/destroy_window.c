/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:45:59 by znichola          #+#    #+#             */
/*   Updated: 2023/05/25 13:11:24 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	destroy_window(t_app *a)
{
	mlx_destroy_window(a->mlx_instance, a->window);
	exit(0);
	return (0);
}

	//free the objects lists from our scene
	// cleanup_scene(&a->s);
