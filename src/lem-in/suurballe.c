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

// void			close_link(t_vertex *vrtx)
// {
// 	t_vertex	*neighbor;
// 	int			i;

// 	neighbor = vrtx->neighbor;
// 	i = 0;
// 	while (i < neighbor->count_edges)
// 	{
// 		if (neighbor->adj[i].vrtx == vrtx)
// 		{
// 			neighbor->adj[i].status == LI_CLOSE;
// 			break ;
// 		}
// 		++i;
// 	}
// }

void			pop_queue(t_queue **queue)
{
	t_queue		*head;

	head = *queue;
	*queue = (*queue)->next;
	free(head);
	head = NULL;
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
		if (!(new = (t_queue *)ft_memalloc(sizeof(t_queue))))
			error(strerror(errno));
		new->prev = *last;
		new->vertex = vertex;
		(*last)->next = new;
		*last = new;
	}
}

void			clean_queue(t_queue **queue, t_queue **last)
{
	t_queue		*tmp;
	t_queue		*free_tmp;

	tmp = *queue;
	if (tmp)
		while (tmp)
		{
			free_tmp = tmp;
			tmp = tmp->next;
			free(free_tmp);
		}
	*queue = NULL;
	*last = NULL;
}

t_vertex		*bfs(t_queue *queue, t_vertex **list_adj, t_queue *last)
{
	t_vertex	*adj;
	int			i;

	enqueue(&queue, list_adj[0], &last);
	while (queue)
	{
		adj = list_adj[queue->vertex->id]; //! если попал на разделенную вершину, то надо идти в сторону родителя
		pop_queue(&queue);
		if (adj->splited == true && adj->neighbor->splited == false)
		{
			if (!adj->adj[adj->adj_index].vrtx->marked)
			{
				adj->adj[adj->adj_index].vrtx->marked = true;
				adj->adj[adj->adj_index].vrtx->neighbor = adj;
				enqueue(&queue, adj->adj[i].vrtx, &last);
			}
			continue ;
		}
		i = 0;
		while (i < adj->count_edges)
		{
			if (adj->adj[i].vrtx->type == LI_END && adj->adj[i].status == LI_OPEN)
			{
				clean_queue(&queue, &last);
				adj->adj[i].vrtx->neighbor = adj;
				adj->adj_index = i;
				return (adj->adj[i].vrtx);
			}
			else if (!adj->adj[i].vrtx->marked && adj->adj[i].status == LI_OPEN)
			{
				enqueue(&queue, adj->adj[i].vrtx, &last);
				adj->adj[i].vrtx->marked = true;
				// adj->adj[i].vrtx->dist = adj->dist + 1;
				adj->adj[i].vrtx->neighbor = adj;
				adj->adj_index = i;
			}
			++i;
		}
	}
	return (NULL);
}

void			split_vertex(t_vertex *path)
{
	while (path->type != LI_START)
	{
		// close_link(path);
		path->neighbor->adj[path->adj_index].status = LI_CLOSE;
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
	while ((path = bfs(queue, li->list_adj, last)))
	{
		
		split_vertex(path);
	}
}
