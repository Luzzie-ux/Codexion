/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:39:43 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/04 16:09:01 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

static void	seat_coders(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->config.size)
	{
		table->coders[i].table = table;
		table->coders[i].left = &table->dongles[i];
		table->coders[i].right = &table->dongles[(i + 1) % table->config.size];
		i++;
	}
}

t_table	*new_table(t_config *config)
{
	t_table	*table;

	table = ft_calloc(config->size, sizeof(t_table));
	if (!table)
		return (NULL);
	table->config = *config;
	table->coders = new_coder_arr(config->size, config->deadline);
	table->dongles = new_dongle_arr(config->size, config->cooldown);
	if (!table->coders || !table->dongles)
		return (del_table(table), NULL);
	seat_coders(table);
	return (table);
}

void	del_table(t_table *table)
{
	del_coder_arr(table->coders, table->config.size);
	table->coders = NULL;
	del_dongle_arr(table->dongles, table->config.size);
	table->dongles = NULL;
	free(table);
}
