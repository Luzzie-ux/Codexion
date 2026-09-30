/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:17:12 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/30 00:45:18 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

# include "env.h"

//PREPROCESSING:
_Bool		parser(const char **args);

//SCHEDULER:
_Bool		scheduler(t_table *table);
uint64_t	*fifo(const t_table *table);
uint64_t	*lifo(const t_table *table);
uint64_t	*edf(const t_table *table);

//RUNTIME:
_Bool		runtime(t_table *table, uint64_t*(*f)(const t_table *table));

#endif
