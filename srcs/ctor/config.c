/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:43:51 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/28 14:50:58 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static t_sched	sched(const char *str)
{
	if (!strcmp(str, "FIFO"))
		return (FIFO);
	else if (!strcmp(str, "LIFO"))
		return (LIFO);
	else if (!strcmp(str, "EDF"))
		return (EDF);
	fprintf(stderr, "Error: Invalid scheduling algorithm '%s'\n", str);
	return (INVALID);
}

static void	*assign(t_config *cfg, int i)
{
	bool	error;
	int		j;
	
	j = 0;
	error = false;
	while(j < i-1){
		if (cfg->values[j] <= 0){
			fprintf(stderr, "Error: Invalid value for argument nº%d\n", j+1);
			error = true;
		}
		j++;
	}
	if (error)
		return (NULL);
	cfg->size = cfg->values[0];
	cfg->deadline = cfg->values[1];
	cfg->compile = cfg->values[2];
	cfg->debug = cfg->values[3];
	cfg->refactor = cfg->values[4];
	cfg->tasks = cfg->values[5];
	cfg->cooldown = cfg->values[6];
	return (cfg);
}

static void *ft_calloc(size_t count, size_t size)
{
	void *ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, count * size);
	return (ptr);
}

t_config	config(const int size, const char **args)
{
	int			i;
	t_config	cfg;

	i = 0;
	cfg.schedule = INVALID;
	if (size != 8){
		fprintf(stderr, "Error: expected 8 args, got %d\n", size);
		return ((t_config){0});
	}
	cfg.values = ft_calloc(size, sizeof(int));
	if (!cfg.values)
		return ((t_config){0});
	while(i < size)
	{
		if (i == 7)
			cfg.schedule = sched(args[i]);
		cfg.values[i] = atoi(args[i]);
		i++;
	}
	if (cfg.schedule == INVALID)
		return (free(cfg.values), cfg.values = NULL, (t_config){0});
	if (!assign(&cfg, i))
		return (free(cfg.values), cfg.values = NULL, (t_config){0});
	return(free(cfg.values), cfg);
}

int main(int argc, char **argv){
	t_config cfg;
	
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <arguments>\n", argv[0]);
		return (0);
	}
	cfg = config(argc-1, argv+1);
	if (!cfg.values || cfg.schedule == INVALID)
		return (1);
	return (cfg.values = NULL, 0);
}