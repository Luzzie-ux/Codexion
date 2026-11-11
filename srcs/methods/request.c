/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:54:31 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/11 22:12:37 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	swap(t_request *r1, t_request *r2)
{
	t_request	tmp;

	tmp = *r1;
	*r1 = *r2;
	*r2 = tmp;
}

int	priority(t_request *r1, t_request *r2, t_sched sched)
{
	if (sched == FIFO)
		return (r1->ticket < r2->ticket);
	else if (sched == LIFO)
		return (r1->ticket > r2->ticket);
	else if (sched == EDF)
	{
		if (r1->deadline != r2->deadline)
			return (r1->deadline < r2->deadline);
	}
	return (heap_priority(r1, r2, FIFO));
}

void	reorder(t_heap *self, t_request req, long i);

void	push(t_heap *self, t_request *req);

void	pop(t_heap *self, t_request *req);
