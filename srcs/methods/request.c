/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:54:31 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/12 15:04:25 by rodrpere         ###   ########.fr       */
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
	return (priority(r1, r2, FIFO));
}

int	heapify(t_dongle *d, int i)
{
	int	right;
	int	left;
	int	best;

	right = (2 * i) + 2;
	left = (2 * i) + 1;
	best = left;
	if (right >= d->queue.size)
		return (best);
	if (priority(&d->queue.arr[right], &d->queue.arr[left], d->queue.sched))
		best = right;
	return (best);
}

void	push(t_dongle *d, t_request *req)
{
	int	pos;
	int	parent;

	d->queue.arr[d->queue.size] = *req;
	pos = (int)d->queue.size++;
	while (pos > 0)
	{
		parent = (pos - 1) / 2;
		if (priority(&d->queue.arr[pos], &d->queue.arr[parent], d->queue.sched))
		{
			swap(&d->queue.arr[pos], &d->queue.arr[parent]);
			pos = parent;
		}
		else
			break ;
	}
}

void	pop(t_dongle *d)
{
	int	pos;
	int	best;

	if (d->queue.size == 0)
		return ;
	d->queue.arr[0] = d->queue.arr[d->queue.size - 1];
	d->queue.size--;
	pos = 0;
	while ((2 * pos) + 1 < d->queue.size)
	{
		best = heapify(d, pos);
		if (priority(&d->queue.arr[best], &d->queue.arr[pos], d->queue.sched))
		{
			swap(&d->queue.arr[pos], &d->queue.arr[best]);
			pos = best;
		}
		else
			break ;
	}
}
