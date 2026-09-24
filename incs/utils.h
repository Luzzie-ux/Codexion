/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 12:06:16 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/24 13:29:05 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdio.h>
#include <stdbool.h>
// ERRORS:
_Bool	error(int status);
_Bool	usage(void);

//MEMORY:
void	*ft_memset(void *s, int c, size_t n);

//STRINGS:
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);

//PARSING:
_Bool parser(char **argv);

#endif
