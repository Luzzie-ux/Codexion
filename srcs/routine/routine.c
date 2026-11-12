/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:55:02 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/12 18:30:41 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <unistd.h>

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

void	*routine(void *arg)
{
	t_coder	*coder;
	t_table	*table;

	coder = (t_coder *)arg;
	table = coder->table;
	while (get_is_over(table) != true)
	{
		if (!compiling(coder))
			return (NULL);
		if (get_is_over(table) != true)
			debuging(coder);
		if (get_is_over(table) != true)
			refactoring(coder);
	}
	return (arg);
}

bool	simulation(t_table *t)
{
	int	i;
	int	created;

	i = 0;
	t->start_tm = now_ms();
	while (i < t->config.size)
		t->coders[i++].last = t->start_tm;
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
