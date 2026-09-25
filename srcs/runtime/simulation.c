/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 13:55:34 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/25 14:04:18 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "env.h"
#include <stdint.h>
#include <stdlib.h>

_Bool	fifo_runtime(t_table *table)
{
	uint64_t	i;

	i = 0;
	while (table->compiles > 0)
	{
		table->order = fifo(table);
		if (!table->order)
			return (free(table->coders), free(table->dongle), true);
		while (i < table->size)
		{
			table->coders[table->order[i]];
		}
		free(table->order);
	}
	return (false);
}
