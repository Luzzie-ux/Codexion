/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:44:03 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/30 18:33:51 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <time.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_signal t_signal;
typedef struct s_config t_config;
typedef struct s_dongle t_dongle;
typedef struct s_coder t_coder;
typedef struct s_table t_table;
typedef struct s_waiter t_waiter;

typedef pthread_mutex_t	t_mutex;
typedef pthread_cond_t	t_cond;
typedef pthread_attr_t	t_attr;
typedef pthread_t		t_thread;

typedef enum e_sched t_sched;
typedef enum e_signal t_signal_type;

typedef enum e_sched
{
				INVALID,
				FIFO,
				LIFO,
				EDF,
}				t_sched;

typedef enum e_signal
{
				REQUEST,
				RESPONSE,
}				t_signal_type;

typedef enum e_action
{
	NONE,
	COMPILING,
	DEBUGING,
	REFACTORING,
	DONE,
} t_action;

typedef struct s_signal
{
	int 			signal_id;
	t_signal_type	type;
	int				coder_id;
	int				left_id;
	int 			right_id;
	bool 			answer;
}				t_signal;

typedef struct s_dongle
{
	int 		uid;
	t_mutex		*mutex;
	t_cond		*cond;
	t_attr		attr;
	bool		is_taken;
	long		cooldown;
	long		free_when;
}				t_dongle;

typedef struct s_coder
{
	int			uid;
	t_dongle	*right;
	t_dongle	*left;
	t_thread	tid;
	t_mutex		*mutex;
	t_cond		*cond;
	long		last;
	time_t		deadline;
	t_action 	state;
}				t_coder;

typedef struct s_config
{
	t_sched		schedule;
	int			size;
	time_t		deadline;
	long		compile;
	long		debug;
	long		refactor;
	int			tasks;
	time_t		cooldown;
	int			*values;
	bool		error;
}				t_config;

// STACK
typedef struct s_table
{
	t_config	config;
	t_coder		*coders;
	t_signal	*responses;
}				t_table;

// MIN HEAP
typedef struct s_waiter
{
	t_dongle	*dongles;
	t_config	config;
	t_signal 	*requests;
	t_thread	monitor;
}				t_waiter;

// Constructors:
t_signal	new_signal(int cid, t_signal_type type);
t_config	new_config(const int ac, const char **av);
t_dongle	new_dongle(int id, time_t cooldown);
t_coder		new_coder(int id, time_t deadline);
t_table		new_table(t_config config);
t_waiter	new_waiter(t_config config);

// Functions:

// Table & Waiter:
void set_responses(t_signal *responses);
void set_requests(t_signal *requests);
t_signal *get_responses(t_waiter *waiter);
t_signal *get_requests(t_table *table);

// Coder:
void *start(void *coder);
t_dongle *compile(t_coder *coder);
void debug(t_coder *coder);
void refactor(t_coder *coder);

void set_left(t_coder *self, t_dongle *left);
void set_right(t_coder *self, t_dongle *right);

// Time Stuff:
long to_ms(void);

#endif
