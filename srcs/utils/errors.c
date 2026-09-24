/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 21:23:08 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/24 13:29:38 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

_Bool	error(int status)
{
	fprintf(stderr, "[ERROR]: ");
	if (status == 0)
		fprintf(stderr, "Empty");
	else if (status == 1)
		fprintf(stderr, "Non-Integer");
	else if (status == 2)
		fprintf(stderr, "Negative");
	else if (status == 3)
		fprintf(stderr, "No FIFO/EDF");
	else if (status == 4)
		fprintf(stderr, "Empty Schedule");
	fprintf(stderr, " Argument\n");
	return (1);
}

_Bool	usage(void)
{
	fprintf(stderr, " <nbr_of_coders> <time_burnout> <time_compile>");
	fprintf(stderr, " <time_debug> <time_refactor> <compiles_required>");
	fprintf(stderr, " <dongle_cooldown> <schedule>\n");
	return (1);
}
