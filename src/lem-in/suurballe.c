/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe->c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student->42->fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:10:06 by cormund           #+#    #+#             */
/*   Updated: 2019/11/21 15:36:09 by cormund          ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				bfs(t_queue *queue, t_vertex **list_adj, t_queue *last)
{
	t_vertex	*adj;
	int			i;

	while (queue)
	{
		adj = list_adj[queue->vertex->id];
		pop_queue(&queue);
		i = 0;
		while (i < adj->count_edges)
		{
			if (adj->adj[i].vrtx->type == LI_END)
			{
				//clean_queue(&queue);
				return (adj);
			}
			else if (!adj->adj[i].vrtx->marked)
			{
				enqueue(&queue, adj->adj[i].vrtx, &last);
				adj->adj[i].vrtx->marked = true;
				adj->adj[i].vrtx->dist = adj->dist + 1;
				adj->adj[i].vrtx->neighbor = adj->type != LI_START ? adj : NULL;
			}
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
	enqueue(&queue, li->list_adj[0], &last);
	li->start->dist = 0;
	li->start->marked = true;
	bfs(queue, li->list_adj, last);
}
