/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 01:45:15 by znichola          #+#    #+#             */
/*   Updated: 2023/05/13 12:16:27 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// /*
// 	loop until it's given back.
// */
// void	give_back(pthread_mutex_t *m, int *lock)
// {
// 	int	have_i_given_back_the_reasource;

// 	have_i_given_back_the_reasource = 1;
// 	while (have_i_given_back_the_reasource)
// 	{
// 		if (try_return_main(m, lock))
// 			have_i_given_back_the_reasource = 0;
// 		usleep(100);
// 	}
// }

/*
	return 1 if was able return the reasource/lock

	returning a reasource is flipping it to 0 so others can use it
	This should theoretically never fail, but how knows.
 */
int	try_return_main(pthread_mutex_t *m, int *lock, int *finished)
{
	int	ret;

	ret = 0;
	if (pthread_mutex_lock(m))
		perror("mutex lock return");
	if (*lock == 1)
	{
		*lock = 0;
		*finished = 0;
		ret = 1;
	}
	if (pthread_mutex_unlock(m))
		perror("mutex unlock return");
	return (ret);
}

/*
	return 1 if was able reserve the reasource/lock

	finished is the flag to tell us if the render was done, if it's 1 it has
	if it's 0 release the lock with out reserving

	reserving a reasrouce is flipping it to 1 if it's not alreay
	this way we tell all the other hungy threads that it's mine!
 */
int	try_reserve_main(pthread_mutex_t *m, int *lock, int *finished)
{
	int	ret;

	ret = 0;
	if (pthread_mutex_lock(m))
		perror("mutex lock reserve");
	if (*lock == 0)
	{
		if (*finished == 1)
		{
			*lock = 1;
			ret = 1;
		}
		else
			ret = 0;
	}
	if (pthread_mutex_unlock(m))
		perror("mutex unlock reserve");
	return (ret);
}


/*
	return 1 if was able reserve the reasource/lock

	finished is the flag to tell us if the render was done, if it's 1 it has
	if it's 0 release the lock with out reserving

	reserving a reasrouce is flipping it to 1 if it's not alreay
	this way we tell all the other hungy threads that it's mine!
 */
int	try_reserve_thread(pthread_mutex_t *m, int *lock, int *finished)
{
	int	ret;

	ret = 0;
	if (pthread_mutex_lock(m))
		perror("mutex lock reserve");
	if (*lock == 0)
	{
		if (*finished == 0)
		{
			*lock = 1;
			ret = 1;
		}
		else
			ret = 0;
	}
	if (pthread_mutex_unlock(m))
		perror("mutex unlock reserve");
	return (ret);
}

/*
	return 1 if was able return the reasource/lock

	returning a reasource is flipping it to 0 so others can use it
	This should theoretically never fail, but how knows.
 */
int	try_return_thread(pthread_mutex_t *m, int *lock, int *finished)
{
	int	ret;

	ret = 0;
	if (pthread_mutex_lock(m))
		perror("mutex lock return");
	if (*lock == 1)
	{
		*finished = 1;
		*lock = 0;
		ret = 1;
	}
	if (pthread_mutex_unlock(m))
		perror("mutex unlock return");
	return (ret);
}

// /*
// 	return the finished of the mutex
//  */
// int	get_mutex_state(pthread_mutex_t *m, int *lock)
// {
// 	int	ret;

// 	ret = 0;
// 	if (pthread_mutex_lock(m))
// 		perror("mutex lock get finished");
// 	ret = *lock;
// 	if (pthread_mutex_unlock(m))
// 		perror("mutex unlock finished");
// 	return (ret);
// }
