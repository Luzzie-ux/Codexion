/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:55:02 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/09 17:51:31 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <time.h>
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
	t_coder	*coder;
	t_table	*table;

	coder = (t_coder *)arg;
	table = coder->table;
	while (get_is_over(table) != true)
	{
		compiling(coder);
		if (get_is_over(table) != true)
			debuging(coder);
		if (get_is_over(table) != true)
			refactoring(coder);
	}
	return (arg);
}

long	now_ms(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_REALTIME, &ts);
	return ((long)(ts.tv_sec * 1000) + (ts.tv_nsec / 1000000));
}

void	precise_sleep(t_table *table, long to_wait)
{
	struct timespec	ts;
	long			deadline;

	deadline = now_ms() + to_wait;
	ts.tv_sec = deadline / 1000;
	ts.tv_nsec = (deadline % 1000) * 1000000;
	pthread_mutex_lock(&table->stop_mutex);
	while (!table->is_over && now_ms() < deadline)
		pthread_cond_timedwait(&table->stop_cond, &table->stop_mutex, &ts);
	pthread_mutex_unlock(&table->stop_mutex);
}
