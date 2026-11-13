/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:40:14 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/13 23:25:27 by rodrpere         ###   ########.fr       */
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
		return (printerr("Error: Expected 8 args, got:%d\n", argc -1), true);
	return (false);
}

static int	codexion_main(t_config *config)
{
	int		error;
	t_table	*table;

	error = 0;
	table = new_table(config);
	if (!table)
		return (printerr("Error: Malloc Failed\n", 0), 1);
	if (!simulation(table))
	{
		printerr("Error: Exiting with status code %d\n", 1);
		error = 1;
	}
	return (del_table(table), error);
}

int	main(int argc, char **argv)
{
	t_config	cfg;

	if (err(argc, argv[0]))
		return (1);
	cfg = config_ctor(argc, (const char **)argv);
	if (cfg.schedule == INVALID)
		return (1);
	return (codexion_main(&cfg));
}
