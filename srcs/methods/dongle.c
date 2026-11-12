/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:40:06 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/12 18:22:59 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <time.h>

static inline bool	is_myturn(t_coder *c, t_dongle *d)
{
	return (!d->is_taken && d->queue.arr[0].coder_id == c->uid
		&& now_ms() >= d->free_when);
}

static void	wait_myturn(t_dongle *d)
{
	struct timespec	ts;

	if (!d->is_taken && now_ms() < d->free_when)
	{
		ts.tv_sec = d->free_when / 1000;
		ts.tv_nsec = (d->free_when % 1000) * 1000000;
		pthread_cond_wait(&d->cond, &d->mutex);
	}
	else
		pthread_cond_wait(&d->cond, &d->mutex);
}

static t_request	request_ctor(t_dongle *d, t_coder *c)
{
	t_request	r;

	r.coder_id = c->uid;
	r.deadline = get_last(c) + d->table->config.deadline;
	pthread_mutex_lock(&d->mutex);
	r.ticket = d->queue.next_id++;
	return (r);
}

bool	send_request(t_dongle *d, t_coder *c)
{
	t_request	req;

	req = request_ctor(d, c);
	heap_push(&d->queue, &req);
	while (!get_is_over(c->table) && !is_myturn(c, d))
		wait_myturn(d);
	if (get_is_over(c->table))
		return (pthread_mutex_unlock(&d->mutex), false);
	heap_pop(&d->queue);
	d->is_taken = true;
	pthread_mutex_unlock(&d->mutex);
	log_state(c->uid, "has taken a dongle", c->table);
	return (true);
}

void	release_dongle(t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	d->is_taken = false;
	d->free_when = now_ms() + d->cooldown;
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->mutex);
}
