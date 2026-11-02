/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:40:14 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/02 15:29:30 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	codexion_main(t_config *config)
{
	t_table	*table;

	table = new_table(config);
	if (table->config.error)
		return (1);
	routine(table);
	return (del_table(table), 0);
}

int	main(int argc, char **argv)
{
	t_config	cfg;

	if (argc < 2)
		return (fprintf(stderr, "Usage: %s <arguments>\n", argv[0]));
	cfg = new_config(argc - 1, (const char **)argv + 1);
	if (cfg.error)
		return (1);
	return (codexion_main(&cfg));
}
