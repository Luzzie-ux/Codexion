/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 13:55:34 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/01 21:28:54 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

_Bool	runtime(t_table *table)
{
	uint64_t	i;

	i = 0;
	while (table->compiles > 0)
	{
		while (i < table->size)
		{
			/*to change*/
			i++;
		}
		table->compiles--;
	}
	return (false);
}
