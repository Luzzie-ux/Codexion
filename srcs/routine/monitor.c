/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 17:00:56 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/04 18:21:44 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdio.h>

static inline void protect_log(t_table *t, long current_tm, t_coder *coder)
{
	pthread_mutex_lock(&t->log_mutex);
	printf("%ld %d burned out\n", current_tm - t->start, coder->uid);
	pthread_mutex_unlock(&t->log_mutex);
}

static inline long get_last(t_coder *coder)
{
	long	time;

	pthread_mutex_lock(&coder->table->stop_mutex);
	time = coder->last;
	pthread_mutex_unlock(&coder->table->stop_mutex);
	return (time);
}

static inline bool	get_is_over(t_table *t)
{
	bool	is_over;

	pthread_mutex_lock(&t->stop_mutex);
	is_over = t->over;
	pthread_mutex_unlock(&t->stop_mutex);
	return (is_over);
}

static inline void stop_all(t_table *t)
{
	int i = 0;
	t_coder *coder;

	pthread_mutex_lock(&t->stop_mutex);
	t->over = true;
	pthread_mutex_unlock(&t->stop_mutex);
	while(i < t->config.size)
	{
		coder = &t->coders[i];
		pthread_mutex_lock(&coder->mutex);
		pthread_cond_broadcast(&coder->cond);
		pthread_mutex_unlock(&coder->mutex);
		i++;
	}
}

void *monitoring(void *arg)
{
	int i;
	long current_tm;
	t_table *t;

	t = (t_table*)arg;
	while(get_is_over(t))
	{
		i = -1;
		current_tm = now_ms();
		while(++i < t->config.size)
		{
			if ((current_tm - get_last(&t->coders[i])) > t->config.deadline)
				return (protect_log(t, current_tm, &t->coders[i]), NULL);
		}
	}
	return (t);
}
