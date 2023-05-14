/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_threads.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 21:39:25 by znichola          #+#    #+#             */
/*   Updated: 2023/05/14 13:31:03 by znichola         ###   ########.fr       */
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

/* mutexes.c */

int		try_reserve_main(pthread_mutex_t *m, int *lock, int *finished);
int		try_return_main(pthread_mutex_t *m, int *lock, int *finished);
int		try_reserve_thread(pthread_mutex_t *m, int *lock, int *finished);
int		try_return_thread(pthread_mutex_t *m, int *lock, int *finished);

#endif /* minirt */
