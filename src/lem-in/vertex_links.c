/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 01:18:06 by vmormont          #+#    #+#             */
/*   Updated: 2019/11/17 01:43:15 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				link_start(t_vertex *v1, t_vertex *v2)
{
	t_queue		*new;

	if (!(new = (t_queue *)ft_memalloc(sizeof(t_queue))))
		error(strerror(errno));
	if (v1->start == LI_TRUE)
	{
		new->vertex = v2;
		new->next = v1->vertex_link;
		v1->vertex_link = new;
	}
}

int				link_back(t_vertex *v1, t_queue *v2)
{
	t_queue		*new;

	new = v2;
	while (new)
	{
		if (new->vertex == v1 && v2->vertex->end != LI_TRUE)
			return (1);
		new = new->next;
	}
	return (0);
}

void			pop_link(t_queue *link)
{
	t_queue		*new;

	while (link)
	{
		new = link->next;
		free(link);
		link = new;
	}
}

void			create_link(t_vertex *v1, t_vertex *v2)
{
	if (!(v1->vertex_link))
	{
		if (!(v1->vertex_link = (t_queue *)ft_memalloc(sizeof(t_queue))))
			error(strerror(errno));
		v1->vertex_link->vertex = v2;
	}
	else
	{
		if (v1->start == LI_TRUE)
			link_start(v1, v2);
		else
		{
			if (!(link_back(v1, v2->vertex_link)))
				return ;
			pop_link(v1->vertex_link);
			v1->vertex_link = NULL;
			create_link(v1, v2);
		}
	}
}

void			vertex_links(t_path *path)
{
	t_queue		*list;

	list = path->list;
	while (list && list->next)
	{
		create_link(list->vertex, list->next->vertex);
		list = list->next;
	}
}
