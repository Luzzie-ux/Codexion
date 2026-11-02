/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:35:50 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/02 11:39:26 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_signal	new_signal(int cid, t_signal_type type)
{
	t_signal	sig;

	sig = (t_signal){0};
	sig.signal_id = cid;
	sig.coder_id = cid;
	sig.type = type;
	sig.answer = false;
	sig.left_id = -1;
	sig.right_id = -1;
	return (sig);
}
