/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:55:02 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/13 14:51:19 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <unistd.h>

static t_dongles	compare(t_dongle *left, t_dongle *right)
{
	t_dongles	ds;

	ds = (t_dongles){0};
	if (left->uid < right->uid)
		return (ds.first = left, ds.second = right, ds);
	ds.first = right;
	ds.second = left;
	return (ds);
}

void	*compiling(t_coder *coder)
{
	t_dongles	ds;

	ds = compare(coder->left, coder->right);
	if (!get_dongles(&ds, coder))
		return (NULL);
	set_last(coder);
	log_state(coder->uid, "is compiling", coder->table);
	precise_sleep(coder->table, coder->table->config.compile);
	release_dongle(ds.first);
	release_dongle(ds.second);
	inc_comps(coder);
	return (coder);
}

void	*debuging(t_coder *coder)
{
	log_state(coder->uid, "is debugging", coder->table);
	precise_sleep(coder->table, coder->table->config.debug);
	return (coder);
}

void	*refactoring(t_coder *coder)
{
	log_state(coder->uid, "is refactoring", coder->table);
	precise_sleep(coder->table, coder->table->config.refactor);
	return (coder);
}

void	*routine(void *arg)
{
	t_coder	*coder;
	t_table	*table;

	coder = (t_coder *)arg;
	table = coder->table;
	while (get_is_over(table) != true)
	{
		if (!compiling(coder))
			return (NULL);
		if (get_is_over(table) != true)
			debuging(coder);
		if (get_is_over(table) != true)
			refactoring(coder);
	}
	return (arg);
}
