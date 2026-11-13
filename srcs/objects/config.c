/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:43:51 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/13 23:41:02 by rodrpere         ###   ########.fr       */
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
	printerr("Error: Invalid Scheduling Algorithm\n", 0);
	return (INVALID);
}

static t_sched	check(const char *arg, int index)
{
	long	val;
	char	*ptr;

	val = strtol10(arg, &ptr);
	if (val < 0 || val > INT_MAX)
	{
		printerr("Error: Invalid value for argument nº%d\n", index);
		return (INVALID);
	}
	if (ptr == arg || *ptr != '\0')
	{
		printerr("Error: Invalid argument nº%d\n", index);
		return (INVALID);
	}
	return (VALID);
}

static void	assigment(t_config *cfg, const char **args)
{
	int	i;
	int	values[7];

	i = 0;
	while (++i < cfg->size)
		values[i - 1] = atoi(args[i]);
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
	cfg = (t_config){0};
	cfg.size = (long)size - 1;
	while (++i < cfg.size)
	{
		if (check(args[i], i) == INVALID)
			break ;
	}
	assigment(&cfg, args);
	cfg.schedule = sched(args[i]);
	if (cfg.size == 0)
		cfg.schedule = INVALID;
	return (cfg);
}
