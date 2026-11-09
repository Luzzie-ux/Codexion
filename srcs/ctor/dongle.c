/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:33:50 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/09 17:04:36 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdlib.h>

t_dongle	dongle_ctor(long id, t_request *req)
{
	t_dongle	dongle;

	dongle = (t_dongle){0};
	dongle.uid = id;
	dongle.free_when = now_ms();
	dongle.is_taken = false;
	dongle.cooldown = 0;
	dongle.queue = (t_heap){0};
	dongle.queue.arr = req;
	dongle.queue.size = 1;
	dongle.queue.capacity = 2;
	return (dongle);
}

t_dongle	*new_dongle(t_config *cfg)
{
	int			i;
	t_dongle	*dongles;
	t_request	*requests;

	i = 0;
	dongles = ft_calloc(cfg->size, sizeof(t_dongle));
	if (!dongles)
		return (NULL);
	requests = ft_calloc(cfg->size, sizeof(t_request));
	if (!requests)
		return (free(dongles), NULL);
	while (i < cfg->size)
	{
		dongles[i] = dongle_ctor(i + 1, &requests[i]);
		dongles[i].cooldown = cfg->cooldown;
		pthread_mutex_init(&dongles[i].mutex, NULL);
		pthread_cond_init(&dongles[i].cond, NULL);
		i++;
	}
	return (dongles);
}

void	del_dongle(t_dongle *dongles, long size)
{
	int	i;

	if (!dongles)
		return ;
	i = -1;
	while (++i < size)
	{
		pthread_mutex_destroy(&dongles[i].mutex);
		pthread_cond_destroy(&dongles[i].cond);
	}
	free(dongles->queue.arr);
	free(dongles);
	return ;
}
