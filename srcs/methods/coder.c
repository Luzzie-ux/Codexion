/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 16:23:57 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/06 16:33:22 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdio.h>

void	get_dongle(t_coder *c)
{
	long	time;

	time = now_ms() - c->table->start;
	printf("[%ld] Coder %d has taken a dongle\n", time, c->uid);
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
	coder->state = COMPILING;
	get_dongle(coder);
	get_dongle(coder);
	log_action(coder);
	precise_sleep(coder->table, coder->table->config.compile);
	pthread_mutex_lock(&coder->mutex);
	coder->compiles++;
	pthread_mutex_unlock(&coder->mutex);
	return (coder);
}

void	*debuging(t_coder *coder)
{
	coder->state = DEBUGING;
	log_action(coder);
	precise_sleep(coder->table, coder->table->config.debug);
	return (coder);
}

void	*refactoring(t_coder *coder)
{
	coder->state = REFACTORING;
	log_action(coder);
	precise_sleep(coder->table, coder->table->config.refactor);
	return (coder);
}
