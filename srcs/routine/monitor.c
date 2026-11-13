/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 17:00:56 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/13 14:49:55 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void	log_end(t_table *t, long current_tm, t_coder *coder)
{
	long	time;

	pthread_mutex_lock(&t->sim_mutex);
	t->is_over = true;
	time = t->start_tm;
	pthread_mutex_unlock(&t->sim_mutex);
	pthread_mutex_lock(&t->log_mutex);
	printf("%ld %ld burned out\n", current_tm - time, coder->uid);
	pthread_mutex_unlock(&t->log_mutex);
}

static bool	check_burnout(t_table *t)
{
	int		i;
	t_coder	*coders;
	long	time;

	i = 0;
	coders = t->coders;
	time = now_ms();
	while (i < t->config.size)
	{
		if (time - get_last(&coders[i]) > t->config.deadline)
			return (log_end(t, time, &coders[i]), true);
		i++;
	}
	return (false);
}

static bool	check_compiles(t_table *t)
{
	int		i;
	long	compile_count;

	i = 0;
	while (i < t->config.size)
	{
		pthread_mutex_lock(&t->coders[i].mutex);
		compile_count = t->coders[i].compiles;
		pthread_mutex_unlock(&t->coders[i].mutex);
		if (compile_count < t->config.tasks)
			return (false);
		i++;
	}
	return (true);
}

void	*monitoring(void *arg)
{
	t_table	*t;

	t = (t_table *)arg;
	while (get_is_over(t) != true)
	{
		if (check_burnout(t))
			return (stop_all(t), NULL);
		if (check_compiles(t))
			return (stop_all(t), NULL);
		usleep(1000);
	}
	return (NULL);
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
