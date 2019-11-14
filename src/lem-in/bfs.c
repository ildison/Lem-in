/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:54:03 by vmormont          #+#    #+#             */
/*   Updated: 2019/11/14 22:25:16 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define COUNT_START lem_in->link_adj[0].count_edges
#define COUNT_END lem_in->link_adj[lem_in->count_vertexs - 1].count_edges

void			enqueue(t_queue **queue, t_vertex *vertex, t_queue **last)
{
	t_queue		*new;

	if (!*queue)
	{
		if (!(*queue = (t_queue *)ft_memalloc(sizeof(t_queue))))
			exit(0);
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
			exit(0);
		new->prev = *last;
		new->vertex = vertex;
		(*last)->next = new;
		*last = new;
	}
}

int				count_distance(t_queue *queue, t_vertex *vertex, t_queue *last)
{
	t_link		*link;
	int			weight;
	int			i;
	i = 0;
	weight = 0;
	while (queue)
	{
		link = vertex->link;
		while (link)
		{
			weight = vertex->start == LI_TRUE ? 1 : weight;
			
		}
	}
}

int				bfs(t_lem_in *lem_in, t_path **path)
{
	t_queue		*queue;
	t_queue		*last;
	
	queue = NULL;
	last = NULL;
	lem_in->count_path = COUNT_START < COUNT_END ? COUNT_START : COUNT_END;
	enqueue(&queue, lem_in->link_adj[0].vertex, last);
	if (!count_distance(queue, lem_in->link_adj[0].adj, last))
		error(strerror(errno));
	
	
}
