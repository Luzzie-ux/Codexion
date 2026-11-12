/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 16:23:57 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/12 16:40:25 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

bool	get_dongles(t_coder *c)
{
	t_dongles	*ds;

	ds = (t_dongles *){0};
	if (!send_request(ds->small, c))
		return (false);
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

void	*compiling(t_coder *coder)
{
	if (!get_dongles(coder))
		return (coder);
	log_state(coder->uid, "is compiling", coder->table);
	precise_sleep(coder->table, coder->table->config.compile);
	pthread_mutex_lock(&coder->mutex);
	coder->last = now_ms();
	coder->compiles++;
	pthread_mutex_unlock(&coder->mutex);
	return (coder);
}

void	*debuging(t_coder *coder)
{
	log_state(coder->uid, "is debugging", coder->table);
	precise_sleep(coder->table, coder->table->config.debug);
	return (coder);
}

void	*refactoring(t_coder *coder)
{
	log_state(coder->uid, "is refactoring", coder->table);
	precise_sleep(coder->table, coder->table->config.refactor);
	return (coder);
}
