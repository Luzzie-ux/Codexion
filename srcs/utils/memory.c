/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 21:22:39 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/24 12:36:43 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
void	kill(t_table *table)
{
	free(table->coders);
	free(table->dongles);
}
*/

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
