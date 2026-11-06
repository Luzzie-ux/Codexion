/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:18:36 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/06 11:41:08 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

t_request	*new_request_arr(long size)
{
	t_request	*request;

	request = ft_calloc(size, sizeof(t_request));
	if (!request)
		return (NULL);
	return (request);
}

void	del_request(t_request *request)
{
	if (!request)
		return ;
	free(request);
}
