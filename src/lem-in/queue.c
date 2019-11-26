/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 13:10:37 by cormund           #+#    #+#             */
/*   Updated: 2019/11/26 13:35:31 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
			error(LI_ERROR_MALLOC);
		(*queue)->vertex = vertex;
		*last = *queue;
	}
	else
	{
		if (!(new = (t_queue *)ft_memalloc(sizeof(t_queue))))
			error(LI_ERROR_MALLOC);
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
