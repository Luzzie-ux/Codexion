/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:19:04 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/24 18:21:45 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "utils.h"

t_schedule ft_sched(char *schedule)
{
	if (!ft_strncmp(schedule, "fifo", 4))
		return (FIFO);
	if (!ft_strncmp(schedule, "lifo", 4))
		return (LIFO);
	return (EDF);
}
