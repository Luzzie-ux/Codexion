/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 17:49:52 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/16 17:49:54 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

bool	is_digit(const unsigned char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_space(const unsigned char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

long	now_ms(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_REALTIME, &ts);
	return ((long)ts.tv_sec * 1000L + (ts.tv_nsec / 1000000L));
}

int	printerr(const char *s, int i)
{
	return (fprintf(stderr, s, i));
}
