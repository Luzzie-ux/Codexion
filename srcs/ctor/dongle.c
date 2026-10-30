/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 18:46:18 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/30 18:50:56 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

t_dongle	new_dongle(int id, time_t cooldown)
{
	t_dongle dongle;

	dongle = (t_dongle){0};
	dongle.uid = id;
	dongle.free_when = -1;
	dongle.is_taken = false;
	dongle.cooldown = cooldown;
	pthread_mutex_init(dongle.mutex, NULL);
	pthread_cond_init(dongle.cond, NULL);
	pthread_attr_init(&dongle.attr);
	return (dongle);
}
