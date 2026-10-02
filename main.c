/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 14:21:10 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/02 01:04:30 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "env.h"
#include "runtime.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_table table;

	if (argc != 9)
		return (fprintf(stderr, "Usage: %s", argv[0]), usage());
	if (!reservation(&table, (const char **)argv))
		return (1);
	runtime(&table);
	return (0);
}
