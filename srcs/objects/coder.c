/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:33:24 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/13 15:04:38 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdlib.h>

t_coder	coder_ctor(long id)
{
	t_coder	coder;

	coder = (t_coder){0};
	coder.uid = id;
	coder.left = NULL;
	coder.right = NULL;
	coder.last = 0;
	coder.compiles = 0;
	coder.tid = (t_thread){0};
	return (coder);
}

t_coder	*new_coder(t_config *cfg)
{
	long	i;
	t_coder	*coders;

	i = -1;
	coders = ft_calloc(cfg->size, sizeof(t_coder));
	if (!coders)
		return (NULL);
	while (++i < cfg->size)
	{
		coders[i] = coder_ctor(i + 1);
		pthread_mutex_init(&coders[i].mutex, NULL);
		pthread_cond_init(&coders[i].cond, NULL);
	}
	return (coders);
}

void	del_coder(t_coder *coders, long size)
{
	long	i;

	if (!coders)
		return ;
	i = -1;
	while (++i < size)
	{
		pthread_mutex_destroy(&coders[i].mutex);
		pthread_cond_destroy(&coders[i].cond);
	}
	free(coders);
	return ;
}
