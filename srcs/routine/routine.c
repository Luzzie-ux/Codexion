/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:55:02 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/04 15:56:49 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <unistd.h>

const long delay = 1000;

void	*simulation(t_table *table)
{
	table->start = now_ms();
	while (table->config.tasks > 0)
	{
		printf("Routine n %d\n", table->config.tasks);
		routine(table->coders);
		table->config.tasks--;
	}
	return (table);
}

void	*routine(void *arg)
{
	int i;
	t_coder	*coder;
	t_table *table;

	i = 0;
	coder = (t_coder *)arg;
	table = coder->table;
	while(i < table->config.size){
		compiling(&coder[i]);
		debuging(&coder[i]);
		refactoring(&coder[i]);
		i++;
	}
	return (arg);
}

void	*compiling(t_coder *coder)
{
	printf("Coder %d is compiling\n", coder->uid);
	usleep(delay);
	return (coder);
}

void	*debuging(t_coder *coder)
{
	printf("Coder %d is debugging\n", coder->uid);
	usleep(delay);
	return (coder);
}

void	*refactoring(t_coder *coder)
{
	printf("Coder %d is refactoring\n", coder->uid);
	usleep(delay);
	return (coder);
}
