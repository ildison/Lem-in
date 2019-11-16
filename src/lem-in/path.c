/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:10:51 by vmormont          #+#    #+#             */
/*   Updated: 2019/11/17 02:25:25 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			new_path(t_lem_in *lem_in, t_path **path)
{
	t_vertex	*end;
	t_queue		*last;

	end = lem_in->end;
	last = NULL;
	(*path)->step--;
	while (end)
	{
		if (end && end->duplicate)
			begin_enqueue(&(*path)->list, end->neighbor);
		else
			begin_enqueue(&(*path)->list, end);
		if (end->end == LI_TRUE)
			(*path)->endlist = (*path)->list;
		end = end->neighbor;
		(*path)->step++;
	}
}

void			pop_dup(t_vertex *vertex)
{
	t_link		*link;

	
}

void			pop_duplicates(t_path *path)
{
	int			steps;
	t_queue		*new;
	t_queue		*old;

	steps = 0;
	while (steps < path->size)
	{
		new = path[steps].list;
		while (new)
		{
			if (new->vertex->duplicate)
				pop_dup(new->vertex);
			new->vertex->dist = false;
			old = new->next;
			new->next = old->next;
			if (new->next)
				new->next->prev = new;
			free(old);
		}
		new = new->next;
	}
}

int				create_path(t_lem_in *lem_in, t_path **path)
{
	if (!*path)
	{
		if (!(*path = (t_path *)ft_memalloc(sizeof(t_path))))
			error(strerror(errno));
		new_path(lem_in, path);
		(*path)->size = 1;
		vertex_links(*path);
		pop_duplicates(*path);
		if (lem_in->count_path == 1 || lem_in->count_path == 1)
			return (0);
		return (1);
	}
	else
	{
		/* code */
	}
	return (1);
}
