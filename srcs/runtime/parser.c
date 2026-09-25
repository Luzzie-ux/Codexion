/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 21:22:49 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/25 14:27:35 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "env.h"
#include "runtime.h"
#include <stddef.h>

static _Bool	characters(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i] == '-')
		return ((_Bool)error(2));
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return ((_Bool)error(1));
		i++;
	}
	return (false);
}

static _Bool	schedule(char *arg)
{
	if (*arg == '\0')
		return ((_Bool)error(4));
	else if (!ft_strncmp(arg, "fifo", 4))
		return (false);
	else if (!ft_strncmp(arg, "lifo", 4))
		return (false);
	else if (!ft_strncmp(arg, "edf", 3))
		return (false);
	return ((_Bool)error(3));
}

static _Bool	check(char **args)
{
	int	i;

	i = 0;
	if (schedule(args[8]))
		return (true);
	while (++i < 8)
	{
		if (*args[i] == '\0' || !args[i] || !args)
			return ((_Bool)error(0));
		else if (characters(args[i]))
			return (true);
	}
	return (false);
}

_Bool	parser(char **args)
{
	int	i;

	i = 0;
	if (check(args))
		return (true);
	while(++i < 8)
	{
		if (ft_atol(args[i]) == 0)
			return ((_Bool)error(2));
	}
	return (false);
}

void	*preprocess(t_table *table, char **argv)
{
	if (parser(argv))
		return (NULL);
	table->size = ft_atol(argv[1]);
	table->tm_burn = ft_atol(argv[2]);
	table->tm_comp = ft_atol(argv[3]);
	table->tm_debug = ft_atol(argv[4]);
	table->tm_refac = ft_atol(argv[5]);
	table->compiles = ft_atol(argv[6]);
	table->cooldown = ft_atol(argv[7]);
	table->schedule = ft_sched(argv[8]);
	table->dongle = cdongle(table);
	if (!table->dongle)
		return (NULL);
	table->coders = ccoder(table);
	if (!table->coders)
		return (NULL);
	return (table);
}
