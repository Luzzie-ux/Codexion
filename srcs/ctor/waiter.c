/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 18:34:16 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/30 19:00:02 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_waiter	new_waiter(t_config config)
{
	int			i;
	t_waiter	waiter;

	i = 0;
	waiter = (t_waiter){0};
	waiter.config = config;
	waiter.dongles = malloc(sizeof(t_dongle)*config.size);
	if (!waiter.dongles)
		return (waiter.config.error = true, waiter);
	while(i++ < config.size)
		waiter.dongles[i-1] = new_dongle(i, config.cooldown);
	waiter.requests = NULL;
	return (waiter);
}
