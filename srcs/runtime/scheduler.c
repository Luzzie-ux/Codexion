/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 12:07:07 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/02 00:59:54 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

uint64_t	*fifo(const uint64_t size)
{
	uint64_t i;
	uint64_t *res;

	i = 0;
	res = malloc(sizeof(uint64_t) * size);
	if (!res)
		return (NULL);
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
	buf = malloc(sizeof(uint64_t) * size);
	if (!buf)
		return (NULL);
	while (j < size)
	{
		buf[j] = i;
		j++;
		i--;
	}
	return (buf);
}

void		edf(uint64_t *array)
{
	(void)array;
}
