/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:39:43 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/12 15:12:41 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdlib.h>

static void	seat_coders(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->config.size)
	{
		table->coders[i].table = table;
		table->dongles[i].table = table;
		table->coders[i].left = &table->dongles[i];
		table->coders[i].right = &table->dongles[(i + 1) % table->config.size];
		i++;
	}
}

t_table	*new_table(t_config *config)
{
	t_table	*table;

	table = ft_calloc(1, sizeof(t_table));
	if (!table)
		return (NULL);
	table->config = *config;
	table->coders = new_coder(config);
	table->dongles = new_dongle(config);
	pthread_mutex_init(&table->log_mutex, NULL);
	pthread_mutex_init(&table->sim_mutex, NULL);
	pthread_cond_init(&table->sim_cond, NULL);
	if (!table->coders || !table->dongles)
		return (del_table(table), NULL);
	seat_coders(table);
	return (table);
}

void	del_table(t_table *table)
{
	del_coder(table->coders, table->config.size);
	table->coders = NULL;
	del_dongle(table->dongles, table->config.size);
	table->dongles = NULL;
	pthread_mutex_destroy(&table->log_mutex);
	pthread_mutex_destroy(&table->sim_mutex);
	pthread_cond_destroy(&table->sim_cond);
	free(table);
}
