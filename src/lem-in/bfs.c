/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:54:03 by vmormont          #+#    #+#             */
/*   Updated: 2019/11/15 19:00:11 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define COUNT_START lem_in->link_adj[0].count_edges
#define COUNT_END lem_in->link_adj[lem_in->count_vertexs - 1].count_edges

/*
**	Эта функция удаляет вершину из очереди
*/

void			pop_queue(t_queue **queue)
{
	t_queue		*head;

	head = *queue;
	*queue = (*queue)->next;
	free(head);
	head = NULL;
}

/*
**	Эта функция добавляют вершину в очередь
*/


void			begin_enqueue(t_queue **queue, t_vertex *vertex)
{
	t_queue		*new;

	if (!*queue)
	{
		if (!(*queue = (t_queue *)ft_memalloc(sizeof(t_queue))))
			error(strerror(errno));
		(*queue)->vertex = vertex;
	}
	else
	{
		if (!(new = (t_queue *)ft_memalloc(sizeof(t_queue))))
			error(strerror(errno));
		(*queue)->prev = new;
		new->vertex = vertex;
		new->next = *queue;
		*queue = new;
	}
}

void			enqueue(t_queue **queue, t_vertex *vertex, t_queue **last)
{
	t_queue		*new;

	if (!*queue)
	{
		if (!(*queue = (t_queue *)ft_memalloc(sizeof(t_queue))))
			error(strerror(errno));
		(*queue)->vertex = vertex;
		*last = *queue;
	}
	else
	{
		new = *queue;
		while (new)
		{
			if (new->vertex == vertex)
				return ;
			new = new->next;
		}
		if (!(new = (t_queue *)ft_memalloc(sizeof(t_queue))))
			error(strerror(errno));
		new->prev = *last;
		new->vertex = vertex;
		(*last)->next = new;
		*last = new;
	}
}

/*
**	Эта функция будет высчитывать вес вершины (пути)
*/

int				calc_dist(t_queue *queue, t_link_adj *link_adj, t_queue *last)
{
	t_link		*link;
	t_link_adj	adj;
	int			weight;
	int			i;

	while (queue)
	{
		adj = link_adj[queue->vertex->id]; 
		pop_queue(&queue);
		i = 0;
		while (i < adj.count_edges)
		{
			if (adj.adj[i]->end == LI_TRUE)
			{
				// add_neighbor(adj.vertex, ...);
			}
			else if (adj.adj[i] && !adj.adj[i]->marked)
			{
				enqueue(&queue, adj.adj[i], last);
				adj.adj[i]->marked = true;
				adj.adj[i]->dist = adj.vertex->dist + 1;
				adj.adj[i]->neighbor = adj.vertex->start != LI_TRUE ? adj.vertex : NULL;
			}
			else if (adj.adj[i]->marked)
				adj.adj[i]->duplicate = true;
			++i;
		}
	}
	return (1);
}

int				bfs(t_lem_in *lem_in, t_path **path)
{
	t_queue		*queue;
	t_queue		*last;
	
	queue = NULL;
	last = NULL;
	lem_in->count_path = COUNT_START < COUNT_END ? COUNT_START : COUNT_END;
	enqueue(&queue, lem_in->link_adj[0].vertex, last);
	lem_in->start->dist = 0;
	if (!calc_dist(queue, lem_in->link_adj, last))
		error(strerror(errno)); // ????
	create_path(lem_in, path);
	return (0); // ?????
}
