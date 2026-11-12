/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:40:06 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/12 16:40:59 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

static void			is_myturn(void);

static void			wait_myturn(void);

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
	heap_push(d, &req);
	pthread_mutex_unlock(&d->mutex);
	log_state(c->uid, "has taken a dongle", c->table);
}

void	release_dongle(t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	d->is_taken = false;
	d->free_when = now_ms() + d->cooldown;
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->mutex);
}
