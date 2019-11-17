/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:54:03 by vmormont          #+#    #+#             */
/*   Updated: 2019/11/18 01:53:21 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				count_paths(t_lem_in *li)
{
	t_link		*tmp;
	int			start_path;
	int			end_path;
	
	tmp = li->start->links;
	start_path = 0;
	while (tmp)
	{
		tmp = tmp->next;
		++start_path;
	}
	end_path = 0;
	tmp = li->end->links;
	while (tmp)
	{
		tmp = tmp->next;
		++end_path;
	}
	return ((start_path < end_path) ? start_path : end_path);
}

int				breadth_search(t_lem_in *lem_in, t_path **path)
{
	t_queue		*queue;
	t_queue		*last;
	
	queue = NULL;
	last = NULL;
	lem_in->count_path = count_paths(lem_in);
	enqueue(&queue, lem_in->start, &last);
	if (!calc_dist(queue, lem_in->start, last))
		error(strerror(errno));
	create_path(lem_in, path);
	return (1);
}
