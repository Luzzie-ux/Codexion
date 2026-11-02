/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:44:03 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/02 17:36:30 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

typedef struct s_config	t_config;
typedef struct s_dongle	t_dongle;
typedef struct s_coder	t_coder;
typedef struct s_table	t_table;

typedef pthread_mutex_t	t_mutex;
typedef pthread_cond_t	t_cond;
typedef pthread_t		t_thread;

typedef enum e_sched	t_sched;
typedef enum e_action	t_action;

typedef enum e_sched
{
	INVALID,
	FIFO,
	LIFO,
	EDF,
}						t_sched;

typedef enum e_action
{
	NONE,
	COMPILING,
	DEBUGING,
	REFACTORING,
	DONE,
}						t_action;

typedef struct s_dongle
{
	int					uid;
	t_mutex				mutex;
	t_cond				cond;
	bool				is_taken;
	long				cooldown;
	long				free_when;
}						t_dongle;

typedef struct s_coder
{
	int					uid;
	t_dongle			*right;
	t_dongle			*left;
	t_thread			tid;
	t_mutex				mutex;
	long				last;
	time_t				deadline;
	t_action			state;
	t_table				*table;
}						t_coder;

typedef struct s_config
{
	t_sched				schedule;
	int					size;
	time_t				deadline;
	long				compile;
	long				debug;
	long				refactor;
	int					tasks;
	time_t				cooldown;
	int					*values;
	bool				error;
}						t_config;

typedef struct s_table
{
	t_config			config;
	t_coder				*coders;
	t_dongle			*dongles;
	t_thread			monitor;
	t_mutex				log_mutex;
}						t_table;

// Constructors:
t_config				new_config(const int ac, const char **av);
t_dongle				new_dongle(int id, time_t cooldown);
t_dongle				*new_dongle_arr(int size, time_t cooldown);
t_coder					new_coder(int id, time_t deadline);
t_coder					*new_coder_arr(int size, time_t cooldown);
t_table					*new_table(t_config *config);

// Destructors:
void					del_table(t_table *table);
void					del_coder(t_coder *coder);
void					del_coder_arr(t_coder *coders, int size);
void					del_dongle(t_dongle *dongle);
void					del_dongle_arr(t_dongle *dongles, int size);

// Time:
long					to_ms(void);

// Routine:
void					*routine(t_table *table);
void					*simulation(void *arg);
t_dongle				*compiling(t_coder *coder);
void					debuging(t_coder *coder);
void					refactoring(t_coder *coder);

#endif
