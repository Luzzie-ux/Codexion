/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 21:22:32 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/24 13:27:17 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_atoi(const char *nptr)
{
	long		num;
	long		sign;
	char		*ptr;

	num = 0;
	sign = 1;
	ptr = (char *)nptr;
	while (ptr && (*ptr == ' ' || *ptr == '\t'
			|| *ptr == '\n' || *ptr == '\r'
			|| *ptr == '\v' || *ptr == '\f'))
		ptr++;
	if (*ptr == '+')
		ptr++;
	else if (*ptr == '-')
	{
		sign *= -1;
		ptr++;
	}
	while (*ptr >= '0' && *ptr <= '9')
	{
		num = (num * 10) + (*ptr - '0');
		ptr++;
	}
	return (int)(num * sign);
}

long	ft_atol(const char *nptr)
{
	long		num;
	long		sign;
	char		*ptr;

	num = 0;
	sign = 1;
	ptr = (char *)nptr;
	while (ptr && (*ptr == ' ' || *ptr == '\t'
			|| *ptr == '\n' || *ptr == '\r'
			|| *ptr == '\v' || *ptr == '\f'))
		ptr++;
	if (*ptr == '+')
		ptr++;
	else if (*ptr == '-')
	{
		sign *= -1;
		ptr++;
	}
	while (*ptr >= '0' && *ptr <= '9')
	{
		num = (num * 10) + (*ptr - '0');
		ptr++;
	}
	return (num * sign);
}
