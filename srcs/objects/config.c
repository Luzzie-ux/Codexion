/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:43:51 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/13 17:14:16 by rodrpere         ###   ########.fr       */
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

static inline int printerr(const char *s, int i)
{
	return (fprintf(stderr,s, i));
}

static bool check(const char *arg, int index)
{
	long	val;
	char	*ptr;

	val = strtol10(arg, &ptr);
	if (val < 0 || val > INT_MAX)
		return (printerr("Invalid value for argument nº%d", index), true);
	if (ptr == arg || *ptr != '\0')
		return (printerr("Invalid argument nº%d", index), true);
	return (false);
}

static void assigment(t_config *cfg, const char **args);
t_config	config_ctor(const int size, const char **args)
{
	int			i;
	t_config	cfg;

	i = 1;
	cfg.size = (long)size;
	while(i < size - 1){
		cfg.error = check(args[i], i);
		i++;
	}
	if (!cfg.error)
		assigment(&cfg, args);
	return (cfg);
}
