/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 14:07:27 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/25 15:12:31 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void		get_dongle(t_coder *s, t_dongle *d)
{
	if (d->taken)
		return ;
	s->left = d;
	printf("Coder %ld, got left dongle", s->id);
}

_Bool		send_request(t_coder *s, t_dongle *d1, t_dongle *d2)
{
	s->get_dongle(s, d1);
	s->get_dongle(s, d2);
}

t_coder		*ccoder(const t_table *table)
{
	uint64_t	i;
	t_coder		*coders;

	i = 0;
	coders = malloc(sizeof(t_coder) * table->size);
	if (!coders)
		return (NULL);
	while(i < table->size)
	{
		coders[i].action = NONE;
		coders[i].id = i + 1;
		coders[i].left = NULL;
		coders[i].right = NULL;
		coders[i].get_dongle = &get_dongle;
		coders[i].send_request = &send_request;
		i++;
	}
	return (coders);
}
