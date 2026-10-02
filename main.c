/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 14:21:10 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/02 20:02:52 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "env.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_table table;
	int		state;

	if (argc != 9)
		return (usage(argv[0]));
	state = parser((const char **)argv);
	if (state)
		return (1);
	reservation(&table, (const char **)argv);
	if (!constructors(&table))
		return (1);
	printf("YAY! IT WORKS\n");
	return (0);
}
