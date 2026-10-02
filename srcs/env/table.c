/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:19:04 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/02 01:03:23 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "runtime.h"
#include "env.h"
#include <stdlib.h>

static t_schedule	ft_sched(const char *sched)
{
	if (!ft_strncmp(sched, "fifo", 4))
		return (FIFO);
	if (!ft_strncmp(sched, "lifo", 4))
		return (LIFO);
	return (EDF);
}

static uint64_t		*order(t_table *table)
{
	if (table->schedule == LIFO)
		return (lifo(table->size));
	else
		return (fifo(table->size));
}

static void			*ctor(t_table *table)
{
	table->coders = malloc(table->size);
	if (!table->coders)
		return (NULL);
	table->dongles = malloc(table->size);
	if (!table->dongles)
		return (free(table->coders), NULL);
	table->order = order(table);
	if (!table->order)
		return (free(table->coders), free(table->dongles), NULL);
	return (table);
}

t_table				*reservation(t_table *table, const char **argv)
{
	if (parser(argv))
		return (NULL);
	table->size = ft_atol(argv[1]);
	table->tm_burn = ft_atol(argv[2]);
	table->tm_comp = ft_atol(argv[3]);
	table->tm_debug = ft_atol(argv[4]);
	table->tm_refac = ft_atol(argv[5]);
	table->rounds = ft_atol(argv[6]);
	table->cooldown = ft_atol(argv[7]);
	table->schedule = ft_sched(argv[8]);
	if (!ctor(table))
		return (NULL);
	return (table);
}

