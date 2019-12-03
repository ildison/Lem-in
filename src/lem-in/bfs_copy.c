/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:54:03 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/02 16:45:38 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

# define LI_COUNT_ADJACENTS vrx->count_edges

t_vertex		*bfs(t_queue *queue, t_vertex **list_adj, t_queue *last)
{
	t_vertex	*vrx;
	int			i;

	enqueue(&queue, list_adj[0], &last);
	while ((vrx = pop_queue(&queue)))
	{
		i = 0;
		while (i < LI_COUNT_ADJACENTS)
			if (vrx->adj[i].status == LI_OPEN && !vrx->adj[i].v->marked)
			{
				vrx->adj[i].v->marked = true;
				vrx->adj[i].v->neighbor = vrx;
				vrx->adj[i].v->adj_index = i;
				if (vrx->adj[i].v->in)
				{
					vrx->adj[i].v->out->marked = true;
					enqueue(&queue, vrx->adj[i].v->out, &last);
				}
				else if (vrx->adj[i].v->type == LI_END)
					return (vrx->adj[i].v);
				else
					enqueue(&queue, vrx->adj[i].v, &last);
			}
		++i;
	}
	return (NULL);
}
