/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 00:49:48 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/13 15:02:11 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

static bool	loop(unsigned long cutoff, const char **p, unsigned long *n)
{
	bool			overflow;
	unsigned long	lim;

	overflow = false;
	lim = cutoff % 10;
	cutoff /= 10;
	*n = 0;
	while (is_digit((unsigned char)**p))
	{
		if (overflow)
		{
			(*p)++;
			continue ;
		}
		if (*n > cutoff || (*n == cutoff && (unsigned char)(**p - '0') > lim))
			overflow = true;
		else
			*n = (*n * 10) + (**p - '0');
		(*p)++;
	}
	return (overflow);
}

static int	parse(const char **p)
{
	int	neg;

	neg = 1;
	while (is_space((unsigned char)**p))
		(*p)++;
	if (**p == '-')
	{
		neg = -1;
		(*p)++;
	}
	else if (**p == '+')
		(*p)++;
	return (neg);
}

long	strtol10(const char *restrict nptr, char **restrict endptr)
{
	const char		*p;
	const char		*digits;
	int				neg;
	bool			overflow;
	unsigned long	n;

	p = nptr;
	neg = parse(&p);
	digits = p;
	if (neg == -1)
		overflow = loop(-(unsigned long)LONG_MIN, &p, &n);
	else
		overflow = loop(LONG_MAX, &p, &n);
	if (endptr && p == digits)
		*endptr = (char *)nptr;
	else if (endptr && p != digits)
		*endptr = (char *)p;
	if (overflow && neg == -1)
		return (LONG_MIN);
	else if (overflow && neg == 1)
		return (LONG_MAX);
	if (neg == -1)
		return ((long)(0UL - n));
	return ((long)n);
}

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n > 0)
	{
		*p = c;
		p++;
		n--;
	}
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ptr = ft_memset(ptr, 0, count * size);
	return (ptr);
}
