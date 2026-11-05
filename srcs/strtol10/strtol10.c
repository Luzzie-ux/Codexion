/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtol10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 00:49:48 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/05 02:48:37 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>

static inline bool	is_space(const unsigned char c);
static inline bool	is_digit(const unsigned char c);
static int			parse(const char *p);
static bool			loop(unsigned long cutoff, const char *p, unsigned long *n);
long				strtol10(const char *restrict nptr, char **restrict endptr);

long	strtol10(const char *restrict nptr, char **restrict endptr)
{
	const char		*p;
	int				neg;
	bool			overflow;
	unsigned long	n;
	unsigned long	cutoff;

	p = nptr;
	neg = parse(&*p);
	if (neg)
		cutoff = -(unsigned long)LONG_MIN;
	else
		cutoff = LONG_MAX;
	overflow = loop(cutoff, &*p, &n);
	if (endptr && overflow && neg == -1)
		return (*endptr = (char *)p, LONG_MIN);
	else if (endptr && overflow && neg == 1)
		return (*endptr = (char *)nptr, LONG_MAX);
	return (neg * (long)n);
}

static bool	loop(unsigned long cutoff, const char *p, unsigned long *n)
{
	bool			overflow;
	unsigned long	lim;

	overflow = false;
	lim = cutoff % 10;
	cutoff /= 10;
	*n = 0;
	while (is_digit((unsigned char)*p))
	{
		if (overflow)
		{
			p++;
			continue ;
		}
		if (*n > cutoff || (*n == cutoff && (unsigned char)(*p - '0') > lim))
			overflow = true;
		else
		{
			overflow = false;
			*n = (*n * 10) + (*p - '0');
		}
		p++;
	}
	return (overflow);
}

static int	parse(const char *p)
{
	int	neg;

	neg = 1;
	while (is_space((unsigned char)*p))
		p++;
	if (*p == '-')
	{
		neg = -1;
		p++;
	}
	else if (*p == '+')
		p++;
	return (neg);
}

static inline bool	is_digit(const unsigned char c)
{
	return (c > '0' && c < '9');
}

static inline bool	is_space(const unsigned char c)
{
	return (c <= '\r' || c == ' ');
}

#include <stdio.h>
int main(void){
	
	long n = strtol10("                 123456789", (void*)0);
	printf("%ld\n", n);
	return (0);
}
