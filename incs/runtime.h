/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:17:12 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/25 13:49:21 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

# include "env.h"
#include <stdint.h>

//PREPROCESSING:
_Bool		parser(char **args);
void		*preprocess(t_table *table, char **argv);

//SCHEDULER:
_Bool		scheduler(t_table *table);
uint64_t	*fifo(const t_table *table);
uint64_t	*lifo(const t_table *table);
uint64_t	*edf(const t_table *table);

//RUNTIME:
_Bool		fifo_runtime(t_table *table);
_Bool		lifo_runtime(t_table *table);
_Bool		edf_runtime(t_table *table);

#endif
