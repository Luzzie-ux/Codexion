/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 23:27:54 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/17 00:49:07 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

static t_dongles compare(t_dongle *d1, t_dongle *d2)
{
	t_dongles ds;

	ds = (t_dongles){0};
	ds.first = d1;
	ds.second = d2;
	if (d1->uid < d2->uid)
	{
		ds.first = d2;
		ds.second = d1;
	}
	return (ds);
}

static bool availble(t_dongle *d, t_coder *c)
{
	return (!d->is_taken && d->queue.arr[0].coder_id == c->uid
		&& now_ms() >= d->free_when);
}

static void wait(t_coder *c, t_dongle *g)
{
	struct timespec	ts;
	long			t;
 
	t = 0;
	if (!c->left->is_taken && now_ms() < c->left->free_when)
		t = c->left->free_when;
	if (!c->right->is_taken && now_ms() < c->right->free_when
		&& (!t || c->right->free_when < t))
		t = c->right->free_when;
	if (!t)
		return ((void)pthread_cond_wait(&g->cond, &g->mutex));
	ts.tv_sec = t / 1000;
	ts.tv_nsec = (t % 1000) * 1000000;
	pthread_cond_timedwait(&g->cond, &g->mutex, &ts);
}

static bool request(t_dongles *ds, t_coder *c)
{
	t_request r;

	r.coder_id = c->uid;
	r.deadline = get_last(c) + c->table->config.deadline;
	r.ticket = ds->first->queue.next_id++;
	heap_push(&ds->first->queue, &r);
	r.ticket = ds->second->queue.next_id++;
	heap_push(&ds->second->queue, &r);
	while(!get_is_over(c->table) && !availble(ds->first, c))
		wait(c, ds->first);
	if (get_is_over(c->table))
		return (false);
	heap_pop(&ds->second->queue);
	heap_pop(&ds->first->queue);
	ds->first->is_taken = true;
	ds->second->is_taken = true;
	return (true);
}

bool acquire_dongles(t_coder *c){
	t_dongles ds;
	bool done;

	done = true;

	ds = compare(c->left, c->right);
	if (ds.first == ds.second)
		return (log_state(c->uid, "has taken a dongle", c->table), false);
	pthread_mutex_lock(&ds.first->mutex);
	pthread_mutex_lock(&ds.second->mutex);
	done = request(&ds, c);
	pthread_cond_broadcast(&ds.second->cond);
	pthread_mutex_unlock(&ds.second->mutex);
	pthread_cond_broadcast(&ds.first->cond);
	pthread_mutex_unlock(&ds.first->mutex);
	if (done)
	{
		log_state(c->uid, "has taken a dongle", c->table);
		log_state(c->uid, "has taken a dongle", c->table);
	}
	return (done);
}
