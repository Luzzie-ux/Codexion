/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:43:51 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/13 15:03:24 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <limits.h>
#include <stdio.h>

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
	fprintf(stderr, "Error: Invalid scheduling algorithm '%s'\n", str);
	return (INVALID);
}

static void	assign(t_config *cfg, long vals[8], int count)
{
	int	i;

	i = 0;
	cfg->error = false;
	while (i < count)
	{
		if (vals[i] < 0 || vals[i] > INT_MAX)
		{
			fprintf(stderr, "Error: Invalid value for argument nº%d\n", i + 1);
			cfg->error = true;
		}
		i++;
	}
	if (cfg->error)
		return ;
	cfg->size = vals[0];
	cfg->deadline = vals[1];
	cfg->compile = vals[2];
	cfg->debug = vals[3];
	cfg->refactor = vals[4];
	cfg->tasks = vals[5];
	cfg->cooldown = vals[6];
}

t_config	config_ctor(const int size, const char **args)
{
	int			i;
	long		vals[8];
	char		*ptr;
	t_config	cfg;

	i = 0;
	cfg = (t_config){0};
	while (i++ < size - 1)
	{
		vals[i - 1] = strtol10(args[i - 1], &ptr);
		if (ptr)
		{
			fprintf(stderr, "AAA");
		}
	}
	assign(&cfg, vals, size - 1);
	cfg.schedule = sched(args[size - 1]);
	if (cfg.schedule == INVALID)
		cfg.error = true;
	return (cfg);
}
