/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:54:03 by vmormont          #+#    #+#             */
/*   Updated: 2019/11/24 13:20:51 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_vertex		*bfs(t_queue *queue, t_vertex **list_adj, t_queue *last)
{
	t_vertex	*adj;
	int			i;

	enqueue(&queue, list_adj[0], &last);
	while (queue)
	{
		adj = queue->vertex; //! если попал на разделенную вершину, то надо идти в сторону родителя
		pop_queue(&queue);
		if (adj->splited == true && adj->neighbor->splited == false)
		{
			if (!adj->adj[adj->path_index].vrtx->marked)
			{
				adj->adj[adj->path_index].vrtx->marked = true;
				adj->adj[adj->path_index].vrtx->neighbor = adj;
				enqueue(&queue, adj->adj[adj->path_index].vrtx, &last);
			}
			continue ;
		}
		i = 0;
		while (i < adj->count_edges)
		{
			if (adj->adj[i].vrtx->type == LI_END && adj->adj[i].status == LI_OPEN)
			{
				adj->adj[i].vrtx->neighbor = adj;
				adj->adj[i].vrtx->adj_index = i;
				return (adj->adj[i].vrtx);
			}
			else if (!adj->adj[i].vrtx->marked && adj->adj[i].status == LI_OPEN)
			{
				enqueue(&queue, adj->adj[i].vrtx, &last);
				adj->adj[i].vrtx->marked = true;
				adj->adj[i].vrtx->neighbor = adj;
				adj->adj[i].vrtx->adj_index = i;
			}
			++i;
		}
	}
	return (NULL);
}
