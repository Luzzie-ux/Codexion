/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:55:02 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/06 09:59:47 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <unistd.h>

bool	simulation(t_table *t)
{
	int	i;
	int	created;

	i = 0;
	t->start = now_ms();
	while (i < t->config.size)
		t->coders[i++].last = t->start;
	created = 0;
	if (pthread_create(&t->monitor, NULL, monitoring, t))
		return (false);
	while (created < t->config.size)
	{
		if (pthread_create(&t->coders[created].tid, NULL, routine,
				&t->coders[created]))
		{
			stop_all(t);
			break ;
		}
		created++;
	}
	i = 0;
	while (i < created)
		pthread_join(t->coders[i++].tid, NULL);
	pthread_join(t->monitor, NULL);
	return (created == t->config.size);
}

void	*routine(void *arg)
{
	long	tasks;
	t_coder	*coder;
	t_table	*table;

	coder = (t_coder *)arg;
	pthread_mutex_lock(&coder->mutex);
	table = coder->table;
	tasks = coder->compiles;
	pthread_mutex_unlock(&coder->mutex);
	while (tasks < table->config.tasks)
	{
		compiling(coder);
		debuging(coder);
		refactoring(coder);
		tasks++;
	}
	return (arg);
}

void	*compiling(t_coder *coder)
{
	coder->state = COMPILING;
	get_dongle(coder);
	get_dongle(coder);
	coder->last = now_ms();
	log_action(coder);
	precise_sleep(coder->table, coder->table->config.compile * 1000);
	pthread_mutex_lock(&coder->mutex);
	coder->compiles++;
	pthread_mutex_unlock(&coder->mutex);
	return (coder);
}

void	*debuging(t_coder *coder)
{
	coder->state = DEBUGING;
	log_action(coder);
	precise_sleep(coder->table, coder->table->config.debug * 1000);
	return (coder);
}

void	*refactoring(t_coder *coder)
{
	coder->state = REFACTORING;
	log_action(coder);
	precise_sleep(coder->table, coder->table->config.refactor * 1000);
	return (coder);
}
