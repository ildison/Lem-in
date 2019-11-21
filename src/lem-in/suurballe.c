/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:10:06 by cormund           #+#    #+#             */
/*   Updated: 2019/11/21 15:29:11 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				bfs(t_queue *queue, t_vertex **list_adj, t_queue *last)
{
	t_list_adj	adj;
	int			i;

	while (queue)
	{
		adj = list_adj[queue->vertex->id];
		pop_queue(&queue);
		i = 0;
		while (i < adj.count_edges)
		{
			if (adj.adj[i]->end == LI_TRUE)
				return (adj.vertex);
			else if (adj.adj[i] && !adj.adj[i]->marked)
			{
				enqueue(&queue, adj.adj[i], &last);
				adj.adj[i]->marked = true;
				adj.adj[i]->dist = adj.vertex->dist + 1;
				adj.adj[i]->neighbor = adj.vertex->start != LI_TRUE ? adj.vertex : NULL;
			}
			// else if (adj.adj[i]->marked)
			// 	adj.adj[i]->duplicate = true; //дубликат?
			++i;
		}
	}
	return (0);
}

void			suurballe(t_lem_in *li)
{
	t_queue		*queue;
	t_queue		*last;

	queue = NULL;
	last = NULL;
	enqueue(&queue, lem_in->list_adj[0].vertex, &last);
	lem_in->start->dist = 0;
	lem_in->start->marked = 0;
	bfs(queue, li->list_adj, last);
}
