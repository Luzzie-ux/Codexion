/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 12:07:07 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/25 14:05:36 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "utils.h"
#include "runtime.h"
#include <stdint.h>
#include <stdlib.h>

uint64_t	*fifo(const t_table *table)
{
	uint64_t i;
	uint64_t *res;

	i = 0;
	res = malloc(table->size);
	if (!res)
		return (res);
	res[table->size] = 0;
	while (i < table->size)
	{
		res[i] = i;
		i++;
	}
	return (res);
}

uint64_t	*lifo(const t_table *table)
{
	uint64_t i;
	uint64_t j;
	uint64_t *buf;

	i = table->size;
	j = 0;
	buf = malloc(table->size);
	if (!buf)
		return (buf);
	while (j < table->size)
		buf[j++] = i--;
	return (buf);
}

uint64_t	*edf(const t_table *table)
{
	(void)table;
	return (0);
}

_Bool		scheduler(t_table *table)
{
	if (table->schedule == FIFO)
		return (fifo_runtime(table));
	else if (table->schedule == LIFO)
		return (lifo_runtime(table));
	else
		return (edf_runtime(table));
}

t_schedule	ft_sched(char *sched)
{
	if (!ft_strncmp(sched, "fifo", 4))
		return (FIFO);
	if (!ft_strncmp(sched, "lifo", 4))
		return (LIFO);
	return (EDF);
}
