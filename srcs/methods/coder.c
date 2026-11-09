/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 16:23:57 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/06 19:55:34 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

void	get_dongle(t_coder *c)
{
	
	log_state(c->uid, "has taken a dongle", c->table);
}

long	get_last(t_coder *coder)
{
	long	time;

	pthread_mutex_lock(&coder->table->log_mutex);
	time = coder->last;
	pthread_mutex_unlock(&coder->table->log_mutex);
	return (time);
}

void	*compiling(t_coder *coder)
{
	get_dongle(coder);
	get_dongle(coder);
	pthread_mutex_lock(&coder->mutex);
	coder->last = now_ms();
	coder->compiles++;
	pthread_mutex_unlock(&coder->mutex);
	log_state(coder->uid, "is compiling", coder->table);
	precise_sleep(coder->table, coder->table->config.compile);
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
