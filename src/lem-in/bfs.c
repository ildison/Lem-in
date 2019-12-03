/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:54:03 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/03 13:12:27 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				is_open_link(t_lem_in *li, t_vertex *src, t_vertex *dst)
{
	return (li->matrix_adj[src->id][dst->id]);
}

t_vertex		*marked_adjacent(t_queue **queue, t_lem_in *li, t_vertex *vrx, t_queue **last)
{
	int			i;

	i = LI_COUNTER;
	while (++i < LI_COUNT_ADJACENTS)
		if (is_open_link(li, vrx, vrx->adj[i]) == 1 && !vrx->adj[i]->marked)
		{
			// printf("vrx->name %s | vrx->adj[i]->name %s\n", vrx->name, vrx->adj[i]->name);
			vrx->adj[i]->neighbor = vrx;
			// vrx->adj[i]->adj_index = i;
			if (vrx->adj[i]->type == LI_END)
				return (vrx->adj[i]);
			else
				enqueue(queue, vrx->adj[i], last);
			vrx->adj[i]->marked = true;
		}
	return (NULL);
}


t_vertex		*bfs(t_queue *queue, t_lem_in *li, t_queue *last)
{
	t_vertex	*vrx;

	enqueue(&queue, li->list_adj[0], &last);
	while (queue)
	{
		vrx = pop_queue(&queue);
		if (vrx->splited && is_open_link(li, vrx, vrx->neighbor) == 1)
		{
			if (vrx->out->type != LI_START && !vrx->out->marked)
			{
				vrx->out->marked = true;
				vrx->out->neighbor = vrx;
				if ((vrx = marked_adjacent(&queue, li, vrx->out, &last)))
					return (vrx);
			}
		}
		else if ((vrx = marked_adjacent(&queue, li, vrx, &last)))
			return (vrx);
	}
	return (NULL);
}
