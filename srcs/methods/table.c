/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 16:28:28 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/12 15:13:25 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdio.h>

bool	get_is_over(t_table *t)
{
	bool	is_over;

	pthread_mutex_lock(&t->sim_mutex);
	is_over = t->is_over;
	pthread_mutex_unlock(&t->sim_mutex);
	return (is_over);
}

long	get_start(t_table *t)
{
	long	start;

	pthread_mutex_lock(&t->sim_mutex);
	start = t->start_tm;
	pthread_mutex_unlock(&t->sim_mutex);
	return (start);
}

void	log_state(long id, const char *s, t_table *t)
{
	long	time;

	time = get_start(t);
	pthread_mutex_lock(&t->log_mutex);
	printf("[%ld] %ld %s\n", now_ms() - time, id, s);
	pthread_mutex_unlock(&t->log_mutex);
}

void	stop_all(t_table *t)
{
	int		i;
	t_coder	*coder;

	i = 0;
	pthread_mutex_lock(&t->sim_mutex);
	t->is_over = true;
	pthread_cond_broadcast(&t->sim_cond);
	pthread_mutex_unlock(&t->sim_mutex);
	while (i < t->config.size)
	{
		coder = &t->coders[i];
		pthread_mutex_lock(&coder->mutex);
		pthread_cond_broadcast(&coder->cond);
		pthread_mutex_unlock(&coder->mutex);
		i++;
	}
}
