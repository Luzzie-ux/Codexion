/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 12:06:16 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/24 15:16:42 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdio.h>
#include <stddef.h>

// ERRORS:
int		error(int status);
int		usage(void);

//MEMORY:
void	*ft_memset(void *s, int c, size_t n);

//STRINGS:
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);

#endif
