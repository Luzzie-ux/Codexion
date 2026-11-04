/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:33:24 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/04 16:04:49 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdlib.h>

t_coder	new_coder(int id, time_t deadline)
{
	t_coder	coder;

	coder.uid = id;
	coder.left = NULL;
	coder.right = NULL;
	coder.deadline = deadline;
	coder.last = 0;
	coder.state = NONE;
	coder.tid = (t_thread){0};
	return (coder);
}

t_coder	*new_coder_arr(int size, time_t deadline)
{
	int		i;
	t_coder	*coders;

	i = 0;
	coders = ft_calloc(size, sizeof(t_coder));
	if (!coders)
		return (NULL);
	while (i < size)
	{
		coders[i] = new_coder(i + 1, deadline);
		pthread_mutex_init(&coders[i].mutex, NULL);
		i++;
	}
	return (coders);
}

void	del_coder(t_coder *coder)
{
	if (!coder)
		return ;
	pthread_mutex_destroy(&coder->mutex);
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
