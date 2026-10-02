/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 13:55:34 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/02 01:09:48 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "runtime.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

static void cleanenv(t_table *table)
{
	free(table->coders);
	free(table->dongles);
	free(table->order);
}

_Bool	runtime(const t_table *table)
{
	uint64_t	i;
	t_table *p;

	p = (t_table*)table;
	while (p->rounds > 0)
	{
		i = 0;
		printf("[Compile Round - %ld]\n\n", p->rounds);
		if (p->schedule == EDF)
			edf(p->order);
		while (i < p->size)
			i++;
		p->rounds--;
	}
	return (cleanenv(p), false);
}
