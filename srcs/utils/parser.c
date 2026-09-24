/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 21:22:49 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/24 13:30:14 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stddef.h>

static int	characters(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i] == '-')
		return (error(2));
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (error(1));
		i++;
	}
	return (0);
}

static int	scheduler(char *arg)
{
	if (*arg == '\0')
		return (error(4));
	else if (!ft_strncmp(arg, "fifo", 4))
		return (0);
	else if (!ft_strncmp(arg, "edf", 3))
		return (0);
	return (error(3));
}

static int	check(char **args)
{
	int	i;

	i = 0;
	if (scheduler(args[8]))
		return (1);
	while (++i < 8)
	{
		if (*args[i] == '\0' || !args[i] || !args)
			return (error(0));
		else if (characters(args[i]))
			return (1);
	}
	return (0);
}
/*
int	parser(t_table *table, char **argv)
{
	if (check(argv))
		return (1);
	table->elements = ft_atol(argv[1]);
	table->burnout = ft_atol(argv[2]);
	table->compile = ft_atol(argv[3]);
	table->debug = ft_atol(argv[4]);
	table->refactor = ft_atol(argv[5]);
	table->nbr_compiles = ft_atol(argv[6]);
	table->dongle_cooldown = ft_atol(argv[7]);
	table->schedule = ft_atol(argv[8]);
	return (0);
}
*/
