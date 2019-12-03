/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:40:32 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/03 14:32:15 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			valid_ants(char *line)
{
	int				int_ant;
	char			*char_ant;

	if ((int_ant = ft_atoi(line)) > 0)
	{
		char_ant = ft_itoa(int_ant);
		if (ft_strequ(line, char_ant))
		{
			free(char_ant);
			return (int_ant);
		}
	}
	return (0);
}

static int		valid_double(t_lem_in *li)
{
	int			start;
	int			end;
	t_vertex	*tmp;

	start = 0;
	end = 0;
	tmp = li->start;
	while (tmp)
	{
		if (tmp->type == LI_START)
			++start;
		else if (tmp->type == LI_END)
			++end;
		tmp = tmp->next;
	}
	if ((start == 1) && (end == 1))
		return (1);
	return (0);
}

static int		valid_vertexs(t_lem_in *li)
{
	t_vertex	*tmp;
	t_vertex	*tmp2;

	tmp = li->start;
	if (tmp->name[0] == 'L' || !(valid_double(li)))
		return (0);
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strequ(tmp->name, tmp2->name) || tmp2->name[0] == 'L')
				return (0);
			if ((tmp->coord.x == tmp2->coord.x) &&
				(tmp->coord.y == tmp2->coord.y))
				return (0);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

int				validation(t_lem_in *li, char *line)
{
	int			ants;

	if ((ants = valid_ants(line)))
	{
		if (valid_vertexs(li))
		{
			return (ants);
		}
		error(LI_ERROR_NOT_VALID_V);
	}
	error(LI_ERROR_NOT_VALID_ANTS);
	return (-1);
}
