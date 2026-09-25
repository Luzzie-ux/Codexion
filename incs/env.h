/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:13:21 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/25 15:12:59 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <bits/pthreadtypes.h>
#include <iso646.h>
# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
#include <sys/types.h>

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

t_schedule		ft_sched(char *schedule);

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
	_Bool		(*send_request)(t_coder *s, t_dongle *d1, t_dongle *d2);
	void		(*get_dongle)(t_coder *s, t_dongle *d);
}				t_coder;

void			get_dongle(t_coder *s, t_dongle *d);
_Bool			send_request(t_coder *s, t_dongle *d1, t_dongle *d2);

typedef struct s_table
{
	t_coder		*coders;
	t_dongle	*dongle;
	uint64_t	size;
	uint64_t	tm_burn;
	uint64_t	tm_comp;
	uint64_t	tm_debug;
	uint64_t	tm_refac;
	uint64_t	compiles;
	uint64_t	cooldown;
	t_schedule	schedule;
	uint64_t	*order;
}				t_table;

#endif
