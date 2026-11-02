/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:39:43 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/02 15:24:09 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

t_table	*new_table(t_config *config)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->config = *config;
	if (!new_coder_arr(table->coders, config->deadline, config->size))
		return (table->config.error = true, table);
	if (!new_dongle_arr(table->dongles, config->cooldown, config->size))
		return (table->config.error = true, table);
	return (table);
}

void	del_table(t_table *table)
{
	del_coder_arr(table->coders, table->config.size);
	table->coders = NULL;
	del_dongle_arr(table->dongles, table->config.size);
	table->dongles = NULL;
}
