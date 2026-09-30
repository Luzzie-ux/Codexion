/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 00:16:10 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/30 00:56:52 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_dongle *dongle(size_t size)
{
	uint64_t	i;
	t_dongle	*dongles;

	i = 0;
	dongles = malloc(sizeof(t_dongle) * size);
	if (!dongles)
		return (NULL);
	while (i < size)
	{
		dongles[i].taken = false;
		i++;
	}
	return (dongles);
}
