/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 13:55:34 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/30 01:01:12 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "env.h"
#include <stdlib.h>
#include <stdint.h>

_Bool	runtime(t_table *table, uint64_t *(*f)(const t_table *table))
{
	uint64_t	i;

	i = 0;
	while (table->compiles > 0)
	{
		table->order = f(table); 
		if (!table->order)
			return (free(table->coders), free(table->dongles), true);
		while (i < table->size)
		{
			/*to change*/
			i++;
		}
		free(table->order);
		table->compiles--;
	}
	return (false);
}
