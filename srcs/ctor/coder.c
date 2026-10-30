/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 18:12:33 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/30 18:57:50 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder		new_coder(int id, time_t deadline)
{
	t_coder coder;

	coder = (t_coder){0};
	coder.uid = id;
	coder.left = NULL;
	coder.right = NULL;
	coder.deadline = deadline;
	coder.last = -1;
	coder.state = NONE;
	coder.tid = (t_thread){0};
	pthread_mutex_init(coder.mutex, NULL);
	pthread_cond_init(coder.cond, NULL);
	return (coder);
}

void	set_left(t_coder *self, t_dongle *left)
{
	self->left = left;
}

void	set_right(t_coder *self, t_dongle *right)
{
	self->right = right;
}
