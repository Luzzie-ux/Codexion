/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:40:14 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/13 17:12:18 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

static bool err(int argc, char *argv)
{
	int min;
	int max;

	min = 2;
	max = 9;
	if (argc < min)
	{
		fprintf(stderr, "Usage: %s <arguments>\n", argv);
		return (true);
	}
	if (argc != max)
	{
		fprintf(stderr, "Expected %d, got: %d", max - 1, argc - 1);
		return (true);
	}
	return (false);
}

static int	codexion_main(t_config *config)
{
	t_table	*table;

	table = new_table(config);
	if (!table)
		return (1);
	if (!simulation(table))
	{
		fprintf(stderr, "Error: Simulation is Over\n");
		return (del_table(table), 1);
	}
	return (del_table(table), 0);
}

int	main(int argc, char **argv)
{
	t_config	cfg;

	if (err(argc, argv[0]))
		return (1);
	cfg = config_ctor(argc, (const char **)argv);
	if (cfg.error)
		return (1);
	return (codexion_main(&cfg));
}
