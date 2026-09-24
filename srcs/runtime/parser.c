/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 21:22:49 by rodrpere          #+#    #+#             */
/*   Updated: 2026/09/24 15:45:52 by rodrpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "env.h"

static _Bool	characters(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i] == '-')
		return ((_Bool)error(2));
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return ((_Bool)error(1));
		i++;
	}
	return (false);
}

static _Bool	scheduler(char *arg)
{
	if (*arg == '\0')
		return ((_Bool)error(4));
	else if (!ft_strncmp(arg, "fifo", 4))
		return (false);
	else if (!ft_strncmp(arg, "edf", 3))
		return (false);
	return ((_Bool)error(3));
}

static _Bool	check(char **args)
{
	int	i;

	i = 0;
	if (scheduler(args[8]))
		return (true);
	while (++i < 8)
	{
		if (*args[i] == '\0' || !args[i] || !args)
			return ((_Bool)error(0));
		else if (characters(args[i]))
			return (true);
	}
	return (false);
}

_Bool	parser(char **args)
{
	int	i;

	i = 0;
	if (check(args))
		return (true);
	while(++i < 8)
	{
		if (ft_atol(args[i]) == 0)
			return ((_Bool)error(2));
	}
	return (false);
}

void	*preprocess(char **argv);
