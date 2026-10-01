/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:17:12 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/01 21:01:38 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

# include "env.h"

//PARSER:
_Bool		parser(const char **args);

//SCHEDULES:
uint64_t	*fifo(const uint64_t size);
uint64_t	*lifo(const uint64_t size);
uint64_t	*edf(const t_table *table);

//RUNTIME:
_Bool		runtime(t_table *table);

#endif
