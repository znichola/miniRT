/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passthroughs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:24:14 by znichola          #+#    #+#             */
/*   Updated: 2023/05/29 14:51:57 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	multithread_render(t_app *a)
{
	single_thread_render(a);
}

void	render_ui(t_app *a)
{
	(void)a;
}

void	start_threads(t_app *a)
{
	(void)a;
}
