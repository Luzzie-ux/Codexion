/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:44:03 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/09 23:18:30 by rodrpere         ###   ########.fr       */
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
# include <unistd.h>

typedef struct s_heap		t_heap;
typedef struct s_request	t_request;
typedef struct s_config		t_config;
typedef struct s_dongle		t_dongle;
typedef struct s_coder		t_coder;
typedef struct s_table		t_table;

typedef pthread_mutex_t		t_mutex;
typedef pthread_cond_t		t_cond;
typedef pthread_t			t_thread;

typedef enum e_sched		t_sched;

typedef enum e_sched
{
	INVALID,
	FIFO,
	LIFO,
	EDF,
}							t_sched;

typedef struct s_request
{
	long					deadline;
	long					coder_id;
	long					ticket;
}							t_request;

typedef struct s_heap
{
	t_request				*arr;
	long					size;
	long					capacity;
	long					next_id;
}							t_heap;

typedef struct s_dongle
{
	t_mutex					mutex;
	t_cond					cond;
	long					uid;
	long					cooldown;
	long					free_when;
	t_heap					queue;
	t_table					*table;
	bool					is_taken;
}							t_dongle;

typedef struct s_dongles
{
	t_dongle				*small;
	t_dongle				*big;
}							t_dongles;

typedef struct s_coder
{
	t_table					*table;
	t_dongle				*right;
	t_dongle				*left;
	t_thread				tid;
	t_mutex					mutex;
	t_cond					cond;
	time_t					deadline;
	long					last;
	long					compiles;
	long					uid;
}							t_coder;

typedef struct s_config
{
	t_sched					schedule;
	long					deadline;
	long					cooldown;
	long					compile;
	long					debug;
	long					refactor;
	long					tasks;
	long					size;
	long					*values;
	bool					error;
}							t_config;

typedef struct s_table
{
	t_config				config;
	t_dongle				*dongles;
	t_coder					*coders;
	t_thread				monitor;
	t_mutex					log_mutex;
	t_mutex					stop_mutex;
	t_cond					stop_cond;
	long					start;
	bool					is_over;
}							t_table;

// Constructors:
t_config					config_ctor(const int ac, const char **av);
t_dongle					dongle_ctor(long id, t_request *req);
t_dongle					*new_dongle(t_config *cfg);
t_coder						coder_ctor(long id);
t_coder						*new_coder(t_config *cfg);
t_table						*new_table(t_config *config);

// Destructors:
void						del_table(t_table *table);
void						del_coder(t_coder *coders, long size);
void						del_dongle(t_dongle *dongles, long size);

// Coder Routine:
bool						simulation(t_table *table);
void						*routine(void *arg);
void						*compiling(t_coder *coder);
void						*debuging(t_coder *coder);
void						*refactoring(t_coder *coder);
void						get_dongle(t_coder *c);
void						log_state(long id, const char *s, t_table *t);
long						get_last(t_coder *coder);

// Monitor Routine:
bool						get_is_over(t_table *t);
void						stop_all(t_table *t);
void						*monitoring(void *arg);

// Utils:
void						*ft_calloc(size_t count, size_t size);
long						strtol10(const char *restrict nptr, char **endptr);
long						now_ms(void);
void						precise_sleep(t_table *table, long to_wait);

#endif /*CODEXION_H*/
