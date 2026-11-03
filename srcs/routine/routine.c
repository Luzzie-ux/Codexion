/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:55:02 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/03 15:35:22 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>

void	*routine(t_table *table)
{
	return (table);
}

void	*simulation(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	compiling(coder);
	debuging(coder);
	refactoring(coder);
	return (arg);
}

void	*compiling(t_coder *coder)
{
	coder->left = NULL;
	coder->right = NULL;
	return (coder);
}
