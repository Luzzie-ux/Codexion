/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:18:36 by rodrpere          #+#    #+#             */
/*   Updated: 2026/11/03 15:32:55 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_request		new_request(int coder_id, int ticket, long deadline)
{
	t_request request;

	request.coder_id = coder_id;
	request.deadline = deadline;
	request.ticket = ticket;
	return (request);
}

t_request *new_request_arr(int size, int coder_id, int ticket, long deadline)
{
	int i;
	t_request *request;

	i = 0;
	request = malloc(sizeof(t_request)*size);
	if (!request)
		return(NULL);
	while(i < size)
	{
		request[i] = new_request(coder_id, ticket, deadline);
		i++;
	}
	return(request);

}

void		del_request(t_request *request)
{
	if (!request)
		return ;
	free(request);
}
