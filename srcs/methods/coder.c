/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 16:23:57 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/12 22:40:40 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

static t_dongles	compare(t_dongle *left, t_dongle *right)
{
	t_dongles	ds;

	ds = (t_dongles){0};
	if (left->uid < right->uid)
		return (ds.first = left, ds.second = right, ds);
	ds.first = right;
	ds.second = left;
	return (ds);
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

static inline void	set_last(t_coder *c)
{
	pthread_mutex_lock(&c->mutex);
	c->last = now_ms();
	pthread_mutex_unlock(&c->mutex);
}

void	*compiling(t_coder *coder)
{
	t_dongles	ds;

	ds = compare(coder->left, coder->right);
	if (ds.first == ds.second)
		return (log_state(coder->uid, "has taken a dongle", coder->table), NULL);
	if (!get_dongles(&ds, coder))
		return (NULL);
	set_last(coder);
	log_state(coder->uid, "is compiling", coder->table);
	precise_sleep(coder->table, coder->table->config.compile);
	release_dongle(ds.first);
	release_dongle(ds.second);
	pthread_mutex_lock(&coder->mutex);
	coder->compiles++;
	pthread_mutex_unlock(&coder->mutex);
	return (coder);
}
