/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:43:51 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/13 23:12:53 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <limits.h>
#include <stdlib.h>

static int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

static t_sched	sched(const char *str)
{
	if (!ft_strcmp(str, "fifo"))
		return (FIFO);
	else if (!ft_strcmp(str, "edf"))
		return (EDF);
	return (INVALID);
}

static bool check(const char *arg, int index)
{
	long	val;
	char	*ptr;

	val = strtol10(arg, &ptr);
	if (val < 0 || val > INT_MAX)
	{
		printerr("Error: Invalid value for argument nº%d", index);
		return (true);
	}
	if (ptr == arg || *ptr != '\0')
	{
		printerr("Error: Invalid argument nº%d", index);
		return (true);
	}
	if (index == 8 && sched(arg) == INVALID)
	{
		printerr("Error: Invalid Scheduling Algorithm", 0);
		return (true);
	}
	return (false);
}

static void assigment(t_config *cfg, const char **args)
{
	int i;
	int values[cfg->size - 1];

	i = 0;
	while(++i < cfg->size - 1)
		values[i] = atoi(args[i]);
	if (values[0] == 0)
	{
		printerr("Error: Number of Coders is 0", 0);
		cfg->error = true;
	}
	cfg->size = values[0];
	cfg->deadline = values[1];
	cfg->compile = values[2];
	cfg->debug = values[3];
	cfg->refactor = values[4];
	cfg->tasks = values[5];
	cfg->cooldown = values[6];
}

t_config	config_ctor(const int size, const char **args)
{
	int			i;
	t_config	cfg;

	i = 0;
	cfg.size = (long)size;
	while(++i < size)
		cfg.error = check(args[i], i);
	if (!cfg.error)
	{
		assigment(&cfg, args);
		cfg.schedule = sched(args[i]);
	}
	return (cfg);
}
