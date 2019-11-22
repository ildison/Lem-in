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

t_vertex		*bfs(t_queue *queue, t_vertex **list_adj, t_queue *last)
{
	t_vertex	*adj;
	int			i;

	enqueue(&queue, list_adj[0], &last);
	while (queue)
	{
		adj = list_adj[queue->vertex->id]; //! если попал на разделенную вершину, то надо идти в сторону родителя и выйти в сторону неразделенной
		pop_queue(&queue);
		i = 0;
		while (i < adj->count_edges)
		{
			if (adj->adj[i].vrtx->type == LI_END)
			{
				//clean_queue(&queue);
				adj->adj[i].vrtx->neighbor = adj;
				return (adj->adj[i].vrtx);
			}
			else if (!adj->adj[i].vrtx->marked && adj->adj[i].status == LI_OPEN)
			{
				enqueue(&queue, adj->adj[i].vrtx, &last);
				adj->adj[i].vrtx->marked = true;
				adj->adj[i].vrtx->dist = adj->dist + 1;
				adj->adj[i].vrtx->neighbor = adj->type != LI_START ? adj : NULL;
			}
			++i;
		}
	}
	return (NULL);
}

void			close_link(t_vertex *vrtx)
{
	t_vertex	*neighbor;
	int			i;

	neighbor = vrtx->neighbor;
	i = 0;
	while (i < neighbor->count_edges)
	{
		if (neighbor->adj[i].vrtx == vrtx)
		{
			neighbor->adj[i].status == LI_CLOSE;
			break ;
		}
	}
}

void			split_vertex(t_vertex *path)
{
	while (path->type != LI_START)
	{
		close_link(path);
		path->splited = path->type != LI_END ? true : false;
		path = path->neighbor;
	}
}

void			suurballe(t_lem_in *li)
{
	t_queue		*queue;
	t_queue		*last;
	t_vertex	*path;

	queue = NULL;
	last = NULL;
	li->start->marked = true;
	path = bfs(queue, li->list_adj, last);
	split_vertex(path);
}
