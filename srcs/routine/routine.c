/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:55:02 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/04 19:29:25 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

void	*simulation(t_table *table)
{
	int		i;
	int		j;
	t_coder	*coders;

	i = 0;
	j = 0;
	coders = table->coders;
	if (pthread_create(table->monitor, NULL, monitoring, table))
		return (NULL);
	while (i < table->config.size)
	{
		coders[i].last = table->start;
		if (pthread_create(&coders[i].tid, NULL, routine, &coders[i]))
		{
			stop_all(table);
			break ;
		}
		i++;
	}
	while (j < i)
		pthread_join(table->coders[i++].tid, NULL);
	pthread_join(table->monitor, NULL);
	return (table);
}

bool	usimulation(t_table *t)
{
	int	i;
	int	j;

	if (pthread_create(&t->monitor, NULL, monitoring, t))
		return (false);
	t->start = now_ms();
	i = 0;
	while (i < t->config.size)
		t->coders[i++].last = t->start;
	j = -1;
	while (++j < t->config.size)
	{
		if (pthread_create(&t->coders[j].tid, NULL, routine, &t->coders[j]))
		{
			stop_all(t);
			break ;
		}
	}
	i = 0;
	while (i < j)
		pthread_join(t->coders[i++].tid, NULL);
	pthread_join(t->monitor, NULL);
	return (j == t->config.size);
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
