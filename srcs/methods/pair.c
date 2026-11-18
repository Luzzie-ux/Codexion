/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 18:38:33 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/18 11:55:34 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

void	release_dongles(t_pair *ps)
{
	pthread_mutex_lock(&ps->first->mutex);
	pthread_mutex_lock(&ps->second->mutex);
	ps->first->is_taken = false;
	ps->first->free_when = now_ms() + ps->first->cooldown;
	pthread_cond_broadcast(&ps->first->cond);
	ps->second->is_taken = false;
	ps->second->free_when = now_ms() + ps->second->cooldown;
	pthread_cond_broadcast(&ps->second->cond);
	pthread_mutex_unlock(&ps->second->mutex);
	pthread_mutex_unlock(&ps->first->mutex);
}

t_removed	restart(t_coder *c, t_pair *ps)
{
	if (is_free(c->uid, ps->first) && ps->second->is_taken)
	{
		heap_pop(&ps->first->queue);
		pthread_cond_broadcast(&ps->first->cond);
		pthread_mutex_unlock(&ps->first->mutex);
		return (wait(c, ps->second), FIRST);
	}
	else if (is_free(c->uid, ps->second) && ps->first->is_taken)
	{
		heap_pop(&ps->second->queue);
		pthread_cond_broadcast(&ps->second->cond);
		pthread_mutex_unlock(&ps->second->mutex);
		return (wait(c, ps->first), SECOND);
	}
	else
		return (check_dongle(c, ps));
}

void	create_request(t_pair *ps, t_request *r)
{
	if (ps->was_rmvd == FIRST)
		heap_push(&ps->first->queue, r);
	else if (ps->was_rmvd == SECOND)
		heap_push(&ps->second->queue, r);
	else if (ps->was_rmvd == BOTH)
	{
		heap_push(&ps->first->queue, r);
		heap_push(&ps->second->queue, r);
	}
	else
		return ;
}

static bool	loop(t_coder *c, t_pair *ps, t_request *r)
{
	bool	done;

	done = false;
	while (1)
	{
		pthread_mutex_lock(&ps->first->mutex);
		pthread_mutex_lock(&ps->second->mutex);
		if (get_is_over(c->table))
		{
			pthread_mutex_unlock(&ps->second->mutex);
			pthread_mutex_unlock(&ps->first->mutex);
			return (done);
		}
		if (is_free(c->uid, ps->first) && is_free(c->uid, ps->second))
		{
			done = take_dongle(c, ps);
			break ;
		}
		ps->was_rmvd = restart(c, ps);
		create_request(ps, r);
	}
	pthread_mutex_unlock(&ps->second->mutex);
	pthread_mutex_unlock(&ps->first->mutex);
	return (done);
}

bool	acquire_dongles(t_coder *c, t_pair *ps)
{
	t_request	r;
	t_table		*t;
	bool res;

	t = c->table;
	pthread_mutex_lock(&t->log_mutex);
	r.coder_id = c->uid;
	r.deadline = get_last(c) + c->deadline;
	r.ticket = t->ticket_len++;
	pthread_mutex_unlock(&t->log_mutex);
	pthread_mutex_lock(&ps->first->mutex);
	pthread_mutex_lock(&ps->second->mutex);
	ps->was_rmvd = BOTH;
	create_request(ps, &r);
	pthread_mutex_unlock(&ps->second->mutex);
	pthread_mutex_unlock(&ps->first->mutex);
	res = loop(c, ps, &r);
	return (res);
}
