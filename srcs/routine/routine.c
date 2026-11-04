/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:55:02 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/04 19:59:22 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

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
	t_coder	*coder;
	t_table	*table;

	coder = (t_coder *)arg;
	table = coder->table;
	(void)table;
	compiling(coder);
	debuging(coder);
	refactoring(coder);
	return (arg);
}

void	*compiling(t_coder *coder)
{
	coder->state = COMPILING;
	get_dongle(coder);
	get_dongle(coder);
	coder->last = now_ms();
	log_action(coder);
	precise_sleep(coder->table, coder->table->config.compile);
	coder->compiles++;
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
