/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 13:38:18 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/29 13:42:01 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

int main(int argc, char **argv){
	t_config cfg;
	
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <arguments>\n",argv[0]);
		return (0);
	}
	cfg = config(argc-1, (const char **)argv+1);
	if (!cfg.values || cfg.schedule == INVALID)
		return (1);
	for(int i = 0; i < argc-1; i++)
		printf("%s ", argv[i]);
	printf("%s\n", argv[argc-1]);
	return (cfg.values = NULL, 0);
}

