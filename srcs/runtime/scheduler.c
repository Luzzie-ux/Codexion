/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 12:07:07 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/01 21:30:41 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "runtime.h"

uint64_t	*fifo(const uint64_t size)
{
	uint64_t i;
	uint64_t *res;

	i = 0;
	res = malloc(size);
	if (!res)
		return (res);
	res[size] = 0;
	while (i < size)
	{
		res[i] = i;
		i++;
	}
	return (res);
}

uint64_t	*lifo(const uint64_t size)
{
	uint64_t i;
	uint64_t j;
	uint64_t *buf;

	i = size;
	j = 0;
	buf = malloc(size);
	if (!buf)
		return (buf);
	while (j < size)
		buf[j++] = i--;
	return (buf);
}

uint64_t	*edf(const t_table *table)
{
	(void)table;
	return (0);
}
