/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 05:38:55 by vmormont          #+#    #+#             */
/*   Updated: 2019/11/18 01:50:55 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void			pop_queue(t_queue **queue)
{
	t_queue		*head;

	if (*queue)
	{
		head = *queue;
		*queue = (*queue)->next;
		free(head);
		head = NULL;
	}
}

int				calc_dist(t_queue *queue, t_vertex *start, t_queue *last)
{
	t_link		*link;
	int			dist;

	dist = 0;
	while (queue)
	{
		link = start->links;
		while (link)
		{
			dist = link->vertex->start == CH_START ? 1 : dist;
			if (!(link->vertex->visited) && link->vertex->start != CH_START)
			{
				enqueue(&queue, link->vertex, &last);
				link->vertex->dist = start->dist + link->weight;
				link->vertex->visited = true;
				link->vertex->neighbor = link->vertex->start != CH_START ? start : NULL;
			}
			link = link->next;
		}
		pop_queue(&queue);
		start = queue ? queue->vertex : start;
	}
	return (dist);
}
