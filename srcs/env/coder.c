/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 14:07:27 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/02 00:35:27 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static _Bool	get_dongle(t_coder *s, t_dongle *d)
{
	if (d->taken)
		return (true);
	s->left = d;
	printf("Coder %ld, got left dongle", s->id);
	return (false);
}

_Bool			send_request(t_coder *s, t_dongle *d1, t_dongle *d2)
{
	_Bool state;

	state = false;
	if (get_dongle(s, d1) || get_dongle(s, d2))
		state = true;
	return (state);
}

t_coder			*coder(size_t size)
{
	uint64_t	i;
	t_coder		*coders;

	i = 0;
	coders = malloc(sizeof(t_coder) * size);
	if (!coders)
		return (NULL);
	while(i < size)
	{
		coders[i].action = NONE;
		coders[i].id = i + 1;
		coders[i].left = NULL;
		coders[i].right = NULL;
		i++;
	}
	return (coders);
}
