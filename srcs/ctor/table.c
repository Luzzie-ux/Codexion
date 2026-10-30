/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 18:21:53 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/30 19:00:40 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_table	new_table(t_config config)
{
	int			i;
	t_table		table;

	i = 0;
	table = (t_table){0};
	table.config = config;
	table.coders = malloc(sizeof(t_coder)*config.size);
	if (!table.coders)
		return (table.config.error = true, table);
	while(i++ < config.size)
		table.coders[i-1] = new_coder(i, config.deadline);
	table.responses = NULL;
	return (table);
}
