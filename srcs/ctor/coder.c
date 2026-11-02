/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:33:24 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/02 15:22:54 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdlib.h>

t_coder	new_coder(int id, time_t deadline)
{
	t_coder	coder;

	coder = (t_coder){0};
	coder.uid = id;
	coder.left = NULL;
	coder.right = NULL;
	coder.deadline = deadline;
	coder.last = -1;
	coder.state = NONE;
	coder.tid = (t_thread){0};
	return (coder);
}

t_coder	*new_coder_arr(t_coder *coders, time_t burnout, int size)
{
	int	i;

	i = 0;
	coders = malloc(sizeof(t_coder) * size);
	if (!coders)
		return (NULL);
	while (i < size)
	{
		coders[i] = new_coder(i + 1, burnout);
		pthread_mutex_init(&coders[i].mutex, NULL);
		pthread_cond_init(&coders[i].cond, NULL);
		i++;
	}
	return (coders);
}

void	del_coder(t_coder *coder)
{
	if (!coder)
		return ;
	pthread_mutex_destroy(&coder->mutex);
	pthread_cond_destroy(&coder->cond);
}

void	del_coder_arr(t_coder *coders, int size)
{
	int	i;

	i = 0;
	if (!coders)
		return ;
	while (i < size)
		del_coder(&coders[i++]);
	free(coders);
	return ;
}
