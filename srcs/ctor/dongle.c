/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:33:50 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/06 19:34:57 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdlib.h>

t_dongle	new_dongle(int id, time_t cooldown)
{
	t_dongle	dongle;

	dongle = (t_dongle){0};
	dongle.uid = id;
	dongle.free_when = now_ms();
	dongle.is_taken = false;
	dongle.cooldown = cooldown;
	return (dongle);
}

t_dongle	*new_dongle_arr(long size, time_t cooldown)
{
	int			i;
	t_dongle	*dongles;
	t_request	*requests;

	i = 0;
	dongles = ft_calloc(size, sizeof(t_dongle));
	if (!dongles)
		return (NULL);
	requests = ft_calloc(size, sizeof(t_request));
	if (!requests)
		return (free(dongles), NULL);
	while (i < size)
	{
		dongles[i] = new_dongle(i + 1, cooldown);
		dongles[i].request = &requests[i];
		pthread_mutex_init(&dongles[i].mutex, NULL);
		pthread_cond_init(&dongles[i].cond, NULL);
		i++;
	}
	return (dongles);
}

void	del_dongle_arr(t_dongle *dongles, long size)
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
	free(dongles->request);
	free(dongles);
	return ;
}
