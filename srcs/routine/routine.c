/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 17:50:13 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/17 18:04:10 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <unistd.h>

static t_pair	compare(t_dongle *left, t_dongle *right)
{
	t_pair	ps;

	ps = (t_pair){0};
	if (left->uid < right->uid)
		return (ps.first = left, ps.second = right, ps);
	ps.first = right;
	ps.second = left;
	return (ps);
}

void	*compiling(t_coder *coder)
{
	t_pair	ps;

	ps = compare(coder->left, coder->right);
	if (ps.first == ps.second)
		return (log_state(coder->uid, "has taken a dongle", coder->table),
			NULL);
	if (!acquire_dongles(coder, &ps))
		return (NULL);
	set_last(coder);
	log_state(coder->uid, "is compiling", coder->table);
	usleep(coder->table->config.compile * 1000);
	release_dongles(&ps);
	set_compiles(coder);
	return (coder);
}

void	*debuging(t_coder *coder)
{
	log_state(coder->uid, "is debugging", coder->table);
	usleep(coder->table->config.debug * 1000);
	return (coder);
}

void	*refactoring(t_coder *coder)
{
	log_state(coder->uid, "is refactoring", coder->table);
	usleep(coder->table->config.refactor * 1000);
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
		compiling(coder);
		if (get_is_over(table) != true)
			debuging(coder);
		if (get_is_over(table) != true)
			refactoring(coder);
	}
	return (arg);
}
