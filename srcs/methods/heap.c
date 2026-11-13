/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:54:31 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/13 12:08:47 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	swap(t_request *r1, t_request *r2)
{
	t_request	tmp;

	tmp = *r1;
	*r1 = *r2;
	*r2 = tmp;
}

static int	priority(t_request *r1, t_request *r2, t_sched sched)
{
	if (sched == FIFO)
		return (r1->ticket < r2->ticket);
	else if (sched == EDF)
	{
		if (r1->deadline != r2->deadline)
			return (r1->deadline < r2->deadline);
	}
	return (priority(r1, r2, FIFO));
}

static int	heapify(t_heap *q, int i)
{
	int	right;
	int	left;
	int	best;

	right = (2 * i) + 2;
	left = (2 * i) + 1;
	best = left;
	if (right >= q->size)
		return (best);
	if (priority(&q->arr[right], &q->arr[left], q->sched))
		best = right;
	return (best);
}

void	heap_push(t_heap *q, t_request *req)
{
	int	pos;
	int	parent;

	q->arr[q->size] = *req;
	pos = (int)q->size++;
	while (pos > 0)
	{
		parent = (pos - 1) / 2;
		if (priority(&q->arr[pos], &q->arr[parent], q->sched))
		{
			swap(&q->arr[pos], &q->arr[parent]);
			pos = parent;
		}
		else
			break ;
	}
}

void	heap_pop(t_heap *q)
{
	int	pos;
	int	best;

	if (q->size == 0)
		return ;
	q->arr[0] = q->arr[q->size - 1];
	q->size--;
	pos = 0;
	while ((2 * pos) + 1 < q->size)
	{
		best = heapify(q, pos);
		if (priority(&q->arr[best], &q->arr[pos], q->sched))
		{
			swap(&q->arr[pos], &q->arr[best]);
			pos = best;
		}
		else
			break ;
	}
}
