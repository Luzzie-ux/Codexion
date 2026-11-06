/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 16:28:28 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/06 16:35:31 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdio.h>

void	log_action(t_coder *c)
{
	t_table	*t;
	long	time;
	char	*str;

	t = c->table;
	pthread_mutex_lock(&t->log_mutex);
	time = now_ms() - t->start;
	str = "";
	if (c->state == COMPILING)
	{
		str = "is compiling";
		c->last = now_ms();
	}
	else if (c->state == DEBUGING)
		str = "is debugging";
	else if (c->state == REFACTORING)
		str = "is refactoring";
	printf("[%ld] Coder %d %s\n", time, c->uid, str);
	pthread_mutex_unlock(&t->log_mutex);
}

void	stop_all(t_table *t)
{
	int		i;
	t_coder	*coder;

	i = 0;
	pthread_mutex_lock(&t->stop_mutex);
	t->over = true;
	pthread_cond_broadcast(&t->stop_cond);
	pthread_mutex_unlock(&t->stop_mutex);
	while (i < t->config.size)
	{
		coder = &t->coders[i];
		pthread_mutex_lock(&coder->mutex);
		pthread_cond_broadcast(&coder->cond);
		pthread_mutex_unlock(&coder->mutex);
		i++;
	}
}

bool	get_is_over(t_table *t)
{
	bool	is_over;

	pthread_mutex_lock(&t->stop_mutex);
	is_over = t->over;
	pthread_mutex_unlock(&t->stop_mutex);
	return (is_over);
}

long	get_start(t_table *t)
{
	long	start;

	pthread_mutex_lock(&t->stop_mutex);
	start = t->start;
	pthread_mutex_unlock(&t->stop_mutex);
	return (start);
}
