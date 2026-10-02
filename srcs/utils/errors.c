/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 21:23:08 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/02 19:46:07 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

int		error(int status)
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

int		usage(const char *name)
{
	fprintf(stderr, "Usage: %s", name);
	fprintf(stderr, " <nbr_of_coders> <time_burnout> <time_compile>");
	fprintf(stderr, " <time_debug> <time_refactor> <compiles_required>");
	fprintf(stderr, " <dongle_cooldown> <schedule>\n");
	return (1);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	if (!s || n == 0)
		return (s);
	p = (unsigned char *)s;
	while (n--)
		*p++ = c;
	return (s);
}
