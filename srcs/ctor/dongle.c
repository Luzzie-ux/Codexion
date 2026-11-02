/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:33:50 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/02 17:28:53 by rodrpere         ###   ########.fr       */
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
	dongle.free_when = -1;
	dongle.is_taken = false;
	dongle.cooldown = cooldown;
	return (dongle);
}

t_dongle	*new_dongle_arr(int size, time_t cooldown)
{
	int	i;
	t_dongle *dongles;

	i = 0;
	dongles = malloc(sizeof(t_dongle) * size);
	if (!dongles)
		return (NULL);
	while (i < size)
	{
		dongles[i] = new_dongle(i + 1, cooldown);
		pthread_mutex_init(&dongles[i].mutex, NULL);
		pthread_cond_init(&dongles[i].cond, NULL);
		i++;
	}
	return (dongles);
}

void	del_dongle(t_dongle *dongle)
{
	if (!dongle)
		return ;
	pthread_mutex_destroy(&dongle->mutex);
	pthread_cond_destroy(&dongle->cond);
}

void	del_dongle_arr(t_dongle *dongles, int size)
{
	int	i;

	i = 0;
	if (!dongles)
		return ;
	while (i < size)
		del_dongle(&dongles[i++]);
	free(dongles);
	return ;
}
