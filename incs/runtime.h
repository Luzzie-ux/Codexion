/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:17:12 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/24 18:04:55 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

# include "env.h"

//PREPROCESSING:
_Bool	parser(char **args);
void	*preprocess(t_table *table, char **argv);
#endif
