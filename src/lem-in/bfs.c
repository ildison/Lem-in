/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:54:03 by vmormont          #+#    #+#             */
/*   Updated: 2019/11/27 16:12:21 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// t_vertex		*bfs(t_queue *queue, t_vertex **list_adj, t_queue *last)
// {
// 	t_vertex	*adj;
// 	int			i;

// 	enqueue(&queue, list_adj[0], &last);
// 	while (queue)
// 	{
// 		adj = queue->vertex; //! если попал на разделенную вершину, то надо идти в сторону родителя
// 		pop_queue(&queue);
// 		if (adj->splited == true && adj->neighbor->splited == false)
// 		{
// 			if (!adj->adj[adj->path_index].vrtx->marked)
// 			{
// 				adj->adj[adj->path_index].vrtx->marked = true;
// 				adj->adj[adj->path_index].vrtx->neighbor = adj;
// 				enqueue(&queue, adj->adj[adj->path_index].vrtx, &last);
// 			}
// 			continue ;
// 		}
// 		i = 0;
// 		while (i < adj->count_edges)
// 		{
// 			if (adj->adj[i].vrtx->type == LI_END && adj->adj[i].status == LI_OPEN)
// 			{
// 				adj->adj[i].vrtx->neighbor = adj;
// 				adj->adj[i].vrtx->adj_index = i;
// 				return (adj->adj[i].vrtx);
// 			}
// 			else if (!adj->adj[i].vrtx->marked && adj->adj[i].status == LI_OPEN)
// 			{
// 				enqueue(&queue, adj->adj[i].vrtx, &last);
// 				adj->adj[i].vrtx->marked = true;
// 				adj->adj[i].vrtx->neighbor = adj;
// 				adj->adj[i].vrtx->adj_index = i;
// 			}
// 			++i;
// 		}
// 	}
// 	return (NULL);
// }

# define LI_COUNT_ADJACENTS vrx->count_edges

t_vertex		*bfs(t_queue *queue, t_vertex **list_adj, t_queue *last)
{
	t_vertex	*vrx;
	int			i;

	enqueue(&queue, list_adj[0], &last);
	while ((vrx = pop_queue(&queue)))
	{
		i = LI_COUNTER;
		while (++i < LI_COUNT_ADJACENTS)
			if (vrx->adj[i].status == LI_OPEN && !vrx->adj[i].vrtx->marked)
			{
				vrx->adj[i].vrtx->neighbor = vrx;
				vrx->adj[i].vrtx->adj_index = i;
				if (vrx->adj[i].vrtx->splited && !vrx->splited)
				{
					vrx->adj[i].vrtx->out->neighbor = vrx->adj[i].vrtx;
					vrx->adj[i].vrtx->out->marked = true;
					enqueue(&queue, vrx->adj[i].vrtx->out, &last);
				}
				else if (vrx->adj[i].vrtx->type == LI_END)
					return (vrx->adj[i].vrtx);
				else
					enqueue(&queue, vrx->adj[i].vrtx, &last);
				vrx->adj[i].vrtx->marked = true;
			}
	}
	return (NULL);
}