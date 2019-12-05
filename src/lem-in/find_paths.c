/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:13:39 by cormund           #+#    #+#             */
/*   Updated: 2019/12/04 20:36:13 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_path	*new_path(t_vertex *vrx)
{
	t_path		*new;
	int			i;

	new = ft_memalloc(sizeof(t_path));
	if (!new)
		error(strerror(errno));
	new->dist = vrx->dist;
	new->v = (t_vertex **)malloc(sizeof(t_vertex *) * new->dist);
	if (!new->v)
		error(strerror(errno));
	i = vrx->dist - 1;
	while (vrx->type != LI_START)
	{
		new->v[i] = vrx;
		vrx = vrx->neighbor;
		--i;
	}
	return (new);
}

static void		add_new_path(t_paths *paths, t_vertex *adj, t_path **last_path)
{
	t_path		*new;

	new = new_path(adj);
	if (*last_path)
		(*last_path)->next = new;
	else
		paths->path = new;
	*last_path = new;
	++paths->count_path;
}

t_paths			find_paths(t_queue **queue, t_lem_in *li, t_queue **last, int n)
{
	t_vertex	*vrx;
	t_paths		path;
	t_path		*last_path;
	int			i;

	last_path = NULL;
	ft_bzero(&path, sizeof(t_paths));
	enqueue(queue, li->list_adj[0], last);
	while ((vrx = pop_queue(queue)))
	{
		i = LI_COUNTER;
		while (++i < vrx->count_edges)
			if (get_edge(li, vrx, vrx->adj[i]) == LI_REVERSE && !LI_ADJ_MARKED)
			{
				vrx->adj[i]->dist = vrx->dist + 1;
				vrx->adj[i]->neighbor = vrx;
				if (vrx->adj[i]->type == LI_END)
					add_new_path(&path, vrx->adj[i], &last_path);
				else if ((vrx->adj[i]->marked = true))
					enqueue(queue, vrx->adj[i], last);
				if (path.count_path == n)
					return (path);
			}
	}
	return (path);
}
