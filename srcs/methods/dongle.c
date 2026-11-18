/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:55:54 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/18 12:01:07 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <time.h>

void	wait(t_coder *c, t_dongle *d)
{
	struct timespec	ts;

	if (get_is_over(c->table))
		return (pthread_mutex_unlock(&d->mutex), (void)0);
	else if (d->queue.arr[0].coder_id != c->uid || d->is_taken)
		pthread_cond_wait(&d->cond, &d->mutex);
	else if (d->queue.arr[0].coder_id == c->uid && !d->is_taken)
	{
		ts = to_ts(d->free_when - now_ms());
		pthread_cond_timedwait(&d->cond, &d->mutex, &ts);
	}
	pthread_mutex_unlock(&d->mutex);
}

bool	is_free(long id, t_dongle *d)
{
	return (d->queue.size > 0 && !d->is_taken && d->queue.arr[0].coder_id == id
		&& now_ms() >= d->free_when);
}

bool	take_dongle(t_coder *c, t_pair *ps)
{
	heap_pop(&ps->first->queue);
	heap_pop(&ps->second->queue);
	ps->first->is_taken = true;
	ps->second->is_taken = true;
	log_state(c->uid, "has taken a dongle", c->table);
	log_state(c->uid, "has taken a dongle", c->table);
	return (true);
}

t_removed	check_dongle(t_coder *c, t_pair *ps)
{
	if (!is_free(c->uid, ps->first))
	{
		pthread_mutex_unlock(&ps->second->mutex);
		wait(c, ps->first);
		return (NONE);
	}
	else
	{
		pthread_mutex_unlock(&ps->first->mutex);
		wait(c, ps->second);
		return (NONE);
	}
}
