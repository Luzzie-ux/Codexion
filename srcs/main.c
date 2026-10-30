/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 13:38:18 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/30 19:30:02 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

static int codexion_main(t_config *config)
{
	t_table table;
	t_waiter waiter;

	table = new_table(*config);
	if (table.config.error)
		return (1);
	waiter = new_waiter(*config);
	if (waiter.config.error)
		return(free(table.coders), 0);
	/*...*/
	return (free(table.coders), free(waiter.dongles), 0);
}

int main(int argc, char **argv)
{
	t_config	cfg;

	if (argc < 2)
		return(fprintf(stderr, "Usage: %s <arguments>\n",argv[0]));
	cfg = new_config(argc-1, (const char **)argv+1);
	if (cfg.error)
		return (1);
	return (codexion_main(&cfg));
}
