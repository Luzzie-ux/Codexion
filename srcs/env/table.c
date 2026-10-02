/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:19:04 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/02 19:54:03 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "env.h"
#include <stdlib.h>

static int	ft_sched(const char *sched)
{
	if (!ft_strncmp(sched, "fifo", 4))
		return (FIFO);
	if (!ft_strncmp(sched, "lifo", 4))
		return (LIFO);
	return (EDF);
}

void		*constructors(t_table *table)
{
	table->coders = coder(table->size);
	if (!table->coders)
		return (NULL);
	table->dongles = dongle(table->size);
	if (!table->dongles)
		return (free(table->coders), NULL);
	return (table);
}

void		reservation(t_table *table, const char **argv)
{
	table->size = ft_atol(argv[1]);
	table->tm_burn = ft_atol(argv[2]);
	table->tm_comp = ft_atol(argv[3]);
	table->tm_debug = ft_atol(argv[4]);
	table->tm_refac = ft_atol(argv[5]);
	table->rounds = ft_atol(argv[6]);
	table->cooldown = ft_atol(argv[7]);
	table->schedule = ft_sched(argv[8]);
}

