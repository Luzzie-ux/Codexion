/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 13:41:32 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/04 15:15:47 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <time.h>
#include <unistd.h>

struct timespec	to_ts(long long ms)
{
	struct timespec	ts;

	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000L;
	return (ts);
}

long long	to_ms(struct timespec *ts)
{
	return ((long long)ts->tv_sec * 1000 + ts->tv_nsec / 1000000);
}

long long	now_ms(void)
{
	struct timespec	now;

	clock_gettime(CLOCK_MONOTONIC, &now);
	return (to_ms(&now));
}
