/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 14:21:10 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/25 14:42:03 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "runtime.h"
#include "env.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_table table;

	if (argc != 9)
		return (fprintf(stderr, "Usage: ./%s", argv[0]), usage());
	preprocess(&table, argv);
	printf("YAY\n");
	return (0);
}
