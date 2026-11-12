/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:07:32 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/12 15:11:54 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	sift_up(t_heap *self);
void	sift_down(t_heap *self);
void	acquire_dongle(t_coder *c);
void	release_dongle(t_coder *c);
