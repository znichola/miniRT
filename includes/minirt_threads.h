/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_threads.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 21:39:25 by znichola          #+#    #+#             */
/*   Updated: 2023/05/13 01:03:16 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_THREADS_H
# define MINIRT_THREADS_H

#include "minirt.h"

/* multithread.c */

void	multithread_render(t_app *a);
void	*thread_routine(void *info_struct);
void	start_threads(t_app *a);

/* give_and_get.c */

void	get_render_lock(t_app *a);
void	release_render_lock(t_app *a);

void	get_start_lock(t_app *a);
void	release_start_lock(t_app *a);

#endif /* minirt */
