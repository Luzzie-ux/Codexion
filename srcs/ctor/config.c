/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:43:51 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/30 18:34:03 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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

static void	assign(t_config *cfg, int count)
{
	int		i;
	
	i = 0;
	cfg->error = false;
	while(i < count)
	{
		if (cfg->values[i] <= 0)
		{
			fprintf(stderr, "Error: Invalid value for argument nº%d\n", i+1);
			cfg->error = true;
		}
		i++;
	}
	if (cfg->error)
		return ;
	cfg->size = cfg->values[0];
	cfg->deadline = cfg->values[1];
	cfg->compile = cfg->values[2];
	cfg->debug = cfg->values[3];
	cfg->refactor = cfg->values[4];
	cfg->tasks = cfg->values[5];
	cfg->cooldown = cfg->values[6];
}

static void	*ft_calloc(size_t count, size_t size)
{
	void *ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, count * size);
	return (ptr);
}

t_config	new_config(const int size, const char **args)
{
	int			i;
	t_config	cfg;

	i = 0;
	cfg = (t_config){0};
	if (size != 8)
	{
		fprintf(stderr, "Error: expected 8 args, got %d\n", size);
		return (cfg.error = true, cfg);
	}
	cfg.values = ft_calloc(size-1, sizeof(int));
	if (!cfg.values)
		return (cfg.error = true, cfg);
	while(i++ < size-1)
		cfg.values[i-1] = atoi(args[i-1]);
	assign(&cfg, size-1);
	cfg.schedule = sched(args[size-1]);
	if (cfg.schedule == INVALID)
		cfg.error = true;
	return(free(cfg.values), cfg.values = NULL, cfg);
}
