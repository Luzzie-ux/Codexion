/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:44:03 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/30 15:42:43 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <bits/pthreadtypes.h>
# include <time.h>
# include <stdbool.h>

typedef struct s_signal t_signal;
typedef struct s_config t_config;
typedef struct s_dongle t_dongle;
typedef struct s_coder t_coder;
typedef struct s_table t_table;
typedef struct s_waiter t_waiter;

typedef pthread_mutex_t	t_mutex;
typedef pthread_cond_t	t_cond;
typedef pthread_t		t_thread;
typedef pthread_attr_t	t_attr;

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

typedef struct s_signal
{
	int 			sid;
	t_signal_type	type;
	int				pid;
	int				lid;
	int 			rid;
	bool 			answer;
}				t_signal;

typedef struct s_dongle
{
	int 		uid;
	t_mutex		*mutex;
	t_cond		*cond;
	t_attr		attr;
	time_t		cooldown;
}				t_dongle;

typedef struct s_coder
{
	int			cid;
	t_dongle	*right;
	t_dongle	*left;
	t_thread	tid;
	t_mutex		*mutex;
	t_cond		*cond;
	t_attr		attr;
	time_t		last;
	bool 		done;
}				t_coder;

typedef struct s_config
{
	int			size;
	time_t		deadline;
	time_t		compile;
	time_t		debug;
	time_t		refactor;
	int			tasks;
	time_t		cooldown;
	t_sched		schedule;
	int			*values;
	bool		error;
}				t_config;

// STACK
typedef struct s_table
{
	t_config	config;
	t_coder		*coders;
	t_signal 	*responses;
}				t_table;

// MIN HEAP
typedef struct s_waiter
{
	t_dongle	*dongles;
	t_config	config;
	t_signal 	*requests;
}				t_waiter;

// Constructors:
t_signal	signal(int id, t_signal_type type);
t_config	config(const int ac, const char **av);
t_dongle	dongle(int id);
t_coder		coder(int id);
t_table		table(t_config config);
t_waiter	waiter(t_config config);

#endif
