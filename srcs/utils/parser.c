/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 21:22:49 by rodrpere          #+#    #+#             */
/*   Updated: 2026/10/02 19:43:42 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static _Bool	characters(const char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return ((_Bool)error(1));
		i++;
	}
	return (false);
}

static _Bool	schedule(const char *arg)
{
	if (*arg == '\0')
		return ((_Bool)error(4));
	else if (ft_strcmp(arg, "fifo") == 0)
		return (false);
	else if (ft_strcmp(arg, "lifo") == 0)
		return (false);
	else if (ft_strcmp(arg, "edf") == 0)
		return (false);
	return ((_Bool)error(3));
}

_Bool	parser(const char **args)
{
	int	i;

	i = 0;
	if (schedule(args[8]))
		return (true);
	while (++i < 8)
	{
		if (*args[i] == '\0' || !args[i] || !args)
			return ((_Bool)error(0));
		else if (characters(args[i]))
			return (true);
		else if (ft_atol(args[i]) <= 0)
			return ((_Bool)error(2));
	}
	return (false);
}
