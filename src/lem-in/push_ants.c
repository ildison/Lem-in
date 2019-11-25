/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:51:32 by vmormont          #+#    #+#             */
/*   Updated: 2019/11/25 13:09:44 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				check_size(int **size)
{
	int			s;
	int			j;


	s = 1;
	if ((*size)[1] - (*size)[0] > 1)
		++(*size)[0];
	else
	{
		j = 0;
		while ((*size)[j] == (*size)[j + 1])
			j++;
		while (j > 0)
		{
			(*size)[j]++;
			j--;
			s++;
		}
	}
	return (s);
}

void			init_dist(int **dist, t_paths finding)
{
	t_path		*path;
	int			i;

	path = finding.path;
	i = 0;
	while (i != finding.count_path)
	{
		dist[i] = path->dist;
		path = path->next;
		i++;
	}
}

void			send_left_ants(t_paths *finding)
{
	t_path		*cur_path;
	int			i;

	i = 0;
	cur_path = finding->path;
	while (cur_path)
	{
		if (cur_path->vrtx[i]->count_ants > 0)
		{
			cur_path->vrtx[i + 1]->count_ants += 1;
			cur_path->vrtx[i]->count_ants -= 1;
		}
		cur_path = cur_path->next;
	}
}

void			push_ants(t_paths finding, t_lem_in *li)
{
	t_path		*path;
	int			dist[finding.count_path + 1];
	int			counter;
	int			need_push_ant;
	int			ants;

	init_dist(&dist, finding);
	path = finding.path;
	ants = 0;
	while (li->end->count_ants != li->count_ants)
	{
		counter = 0;
		need_push_ant = check_size(&(dist));
		while (counter < need_push_ant)
		{
			if (path->vrtx[0]->count_ants == 1)
				send_left_ants(&finding);
			if (li->start->count_ants > 0)
			{
				send_ant(finding, ants);
				li->start->count_ants--;
			}
			++counter;
			++ants;
		}
		write(1, "\n", 1);
	}
		send_ants_to_end(finding);
}