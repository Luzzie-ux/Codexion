/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 17:45:20 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/17 14:47:18 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

long	get_compiles(t_coder *coder)
{
	long	comps;

	pthread_mutex_lock(&coder->mutex);
	comps = coder->compiles;
	pthread_mutex_unlock(&coder->mutex);
	return (comps);
}

void	set_compiles(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->compiles++;
	pthread_mutex_unlock(&coder->mutex);
}

long	get_last(t_coder *coder)
{
	long	time;

	pthread_mutex_lock(&coder->mutex);
	time = coder->last;
	pthread_mutex_unlock(&coder->mutex);
	return (time);
}

void	set_last(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->last = now_ms();
	pthread_mutex_unlock(&coder->mutex);
}
