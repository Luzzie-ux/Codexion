/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:44:03 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/13 23:19:01 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

typedef pthread_mutex_t		t_mutex;
typedef pthread_cond_t		t_cond;
typedef pthread_t			t_thread;

typedef struct s_heap		t_heap;
typedef struct s_request	t_request;
typedef struct s_dongle		t_dongle;
typedef struct s_coder		t_coder;
typedef struct s_config		t_config;
typedef struct s_table		t_table;
typedef enum e_sched		t_sched;

typedef enum e_sched
{
	VALID,
	INVALID,
	FIFO,
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
	t_sched					sched;
}							t_heap;

typedef struct s_dongle
{
	t_table					*table;
	t_heap					queue;
	t_mutex					mutex;
	t_cond					cond;
	long					uid;
	long					cooldown;
	long					free_when;
	bool					is_taken;
}							t_dongle;

typedef struct s_dongles
{
	t_dongle				*first;
	t_dongle				*second;
}							t_dongles;

typedef struct s_coder
{
	t_table					*table;
	t_dongle				*right;
	t_dongle				*left;
	t_thread				tid;
	t_mutex					mutex;
	t_cond					cond;
	long					last;
	long					compiles;
	long					uid;
}							t_coder;

// Simulation Containers:
typedef struct s_config
{
	long					size;
	long					deadline;
	long					compile;
	long					debug;
	long					refactor;
	long					tasks;
	long					cooldown;
	t_sched					schedule;
}							t_config;

typedef struct s_table
{
	t_dongle				*dongles;
	t_coder					*coders;
	t_config				config;
	t_thread				monitor;
	t_mutex					log_mutex;
	t_mutex					sim_mutex;
	t_cond					sim_cond;
	long					start_tm;
	bool					is_over;
}							t_table;

// Default Constructors:
t_config					config_ctor(const int ac, const char **av);
t_dongle					dongle_ctor(long id, t_request *request);
t_coder						coder_ctor(long id);

// Malloc Constructors
t_coder						*new_coder(t_config *cfg);
t_dongle					*new_dongle(t_config *cfg);
t_table						*new_table(t_config *config);

// Malloc Destructors:
void						del_table(t_table *table);
void						del_coder(t_coder *coders, long size);
void						del_dongle(t_dongle *dongles, long size);

// Coder Routine:
bool						simulation(t_table *table);
void						*routine(void *arg);
void						*compiling(t_coder *coder);
void						*debuging(t_coder *coder);
void						*refactoring(t_coder *coder);

// Coder Methods:
void inc_comps(t_coder *coder);
bool						get_dongles(t_dongles *ds, t_coder *coder);
bool						send_request(t_dongle *dongle, t_coder *coder);
void						release_dongle(t_dongle *dongle);
long						get_last(t_coder *coder);
void						set_last(t_coder *coder);

// Heap Methods:
void						heap_push(t_heap *queue, t_request *request);
void						heap_pop(t_heap *queue);

// Monitor Routine:
long						get_start(t_table *table);
bool						get_is_over(t_table *table);
void						stop_all(t_table *table);
void						*monitoring(void *arg);
void						log_state(long id, const char *s, t_table *table);

// Utils:
void						*ft_calloc(size_t count, size_t size);
long						strtol10(const char *restrict nptr, char **endptr);
void						precise_sleep(t_table *table, long to_wait);


// Inline Helpers:
static inline bool	is_digit(const unsigned char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(const unsigned char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static inline long	now_ms(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((long)ts.tv_sec * 1000L + (ts.tv_nsec / 1000000L));
}

static inline int printerr(const char *s, int i)
{
	return (fprintf(stderr,s, i));
}

#endif /*CODEXION_H*/
