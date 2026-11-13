/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 16:23:57 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/13 14:51:56 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

void inc_comps(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->compiles++;
	pthread_mutex_unlock(&coder->mutex);
}

bool	get_dongles(t_dongles *ds, t_coder *c)
{
	if (!send_request(ds->first, c))
		return (false);
	if (!send_request(ds->second, c))
		return (release_dongle(ds->first), false);
	return (true);
}

long	get_last(t_coder *coder)
{
	long	time;

	pthread_mutex_lock(&coder->mutex);
	time = coder->last;
	pthread_mutex_unlock(&coder->mutex);
	return (time);
}

void	set_last(t_coder *c)
{
	pthread_mutex_lock(&c->mutex);
	c->last = now_ms();
	pthread_mutex_unlock(&c->mutex);
}
