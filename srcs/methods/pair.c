/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 18:38:33 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/17 18:53:15 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

void	release_dongles(t_pair *ps)
{
	long	cooldown;

	pthread_mutex_lock(&ps->first->mutex);
	pthread_mutex_lock(&ps->second->mutex);
	cooldown = ps->first->cooldown;
	ps->first->is_taken = false;
	ps->first->cooldown = now_ms() + cooldown;
	pthread_cond_broadcast(&ps->first->cond);
	ps->second->is_taken = false;
	ps->second->cooldown = now_ms() + cooldown;
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
		return (wait(c, ps->second), FIRST);
	}
	else if (is_free(c->uid, ps->second) && ps->first->is_taken)
	{
		heap_pop(&ps->second->queue);
		pthread_cond_broadcast(&ps->second->cond);
		return (wait(c, ps->first), SECOND);
	}
	else
		check_dongle(c, ps);
	return (BOTH);
}

void	create_request(t_pair *ps, t_request *r)
{
	if (ps->was_rmvd == FIRST)
		heap_push(&ps->first->queue, r);
	else if (ps->was_rmvd == SECOND)
		heap_push(&ps->second->queue, r);
	else
	{
		heap_push(&ps->first->queue, r);
		heap_push(&ps->second->queue, r);
	}
}

static bool	loop(t_coder *c, t_pair *ps, t_request *r)
{
	bool	done;

	done = false;
	while (!done)
	{
		if (get_is_over(c->table))
		{
			done = false;
			break ;
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

	t = c->table;
	pthread_mutex_lock(&t->log_mutex);
	r = (t_request){.coder_id = c->uid, .deadline = get_last(c) + c->deadline,
		.ticket = t->ticket_len++};
	pthread_mutex_unlock(&t->log_mutex);
	pthread_mutex_lock(&ps->first->mutex);
	pthread_mutex_lock(&ps->second->mutex);
	create_request(ps, &r);
	return (loop(c, ps, &r));
}
