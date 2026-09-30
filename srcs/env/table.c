/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:19:04 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/30 00:58:02 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "runtime.h"
#include "env.h"

t_table		*reservation(t_table *table, const char **argv)
{
	if (parser(argv))
		return (NULL);
	table->size = ft_atol(argv[1]);
	table->tm_burn = ft_atol(argv[2]);
	table->tm_comp = ft_atol(argv[3]);
	table->tm_debug = ft_atol(argv[4]);
	table->tm_refac = ft_atol(argv[5]);
	table->compiles = ft_atol(argv[6]);
	table->cooldown = ft_atol(argv[7]);
	table->schedule = ft_sched(argv[8]);
	table->dongles = dongle(table->size);
	if (!table->dongles)
		return (NULL);
	table->coders = coder(table->size);
	if (!table->coders)
		return (free(table->dongles), NULL);
	return (table);
}

