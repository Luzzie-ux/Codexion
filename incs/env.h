/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:13:21 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/02 00:32:53 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <bits/pthreadtypes.h>
# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_dongle t_dongle;
typedef struct s_coder t_coder;
typedef struct s_table t_table;

typedef enum e_action
{
				NONE,
				COMPILE,
				DEBUG,
				REFACTOR,
				BURNOUT,
}				t_action;

typedef enum e_schedule
{
				ZERO,
				FIFO,
				LIFO,
				EDF,
}				t_schedule;

typedef struct s_dongle
{
	_Bool		taken;
}				t_dongle;

typedef struct s_coder
{
	uint64_t	id;
	t_dongle	*right;
	t_dongle	*left;
	t_action	action;
	pthread_t	thread;
}				t_coder;

_Bool			send_request(t_coder *s, t_dongle *d1, t_dongle *d2);

typedef struct s_table
{
	t_coder		*coders;
	t_dongle	*dongles;
	uint64_t	size;
	uint64_t	tm_burn;
	uint64_t	tm_comp;
	uint64_t	tm_debug;
	uint64_t	tm_refac;
	uint64_t	rounds;
	uint64_t	cooldown;
	t_schedule	schedule;
	uint64_t	*order;
}				t_table;

//Constructors:
t_dongle	*dongle(size_t size);
t_coder		*coder(size_t size);
t_table		*reservation(t_table *table, const char **argv);

#endif
