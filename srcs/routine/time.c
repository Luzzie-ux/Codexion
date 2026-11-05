/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 13:41:32 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/04 23:57:52 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

long	now_ms(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
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
	while (!table->over && now_ms() < deadline)
		pthread_cond_timedwait(&table->stop_cond, &table->stop_mutex, &ts);
	pthread_mutex_unlock(&table->stop_mutex);
}

void	log_action(t_coder *c)
{
	t_table	*t;
	long	time;
	char	*str;

	t = c->table;
	pthread_mutex_lock(&t->log_mutex);
	time = now_ms() - t->start;
	if (c->state == COMPILING)
		str = "is compiling";
	else if (c->state == DEBUGING)
		str = "is debugging";
	else if (c->state == REFACTORING)
		str = "is refactoring";
	printf("[%ld] Coder %d %s\n", time, c->uid, str);
	pthread_mutex_unlock(&t->log_mutex);
}
