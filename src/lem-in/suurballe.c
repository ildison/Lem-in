/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:05:26 by cormund           #+#    #+#             */
/*   Updated: 2019/12/03 14:28:28 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		clean_marked(t_vertex **list_adj)
{
	while (*list_adj)
	{
		(*list_adj)->marked = false;
		++list_adj;
	}
}

static void		desplitted_vertexs(t_vertex **list_adj)
{
	while (*list_adj)
	{
		(*list_adj)->splited = false;
		(*list_adj)->out = NULL;
		(*list_adj)->neighbor = NULL;
		++list_adj;
	}

}

static void		split_vertex(char **matrix_adj, t_vertex *path)
{
	while (path->type != LI_START)
	{
		matrix_adj[path->neighbor->id][path->id] = LI_REVERSE;
		path->splited = path->type != LI_END ? true : false;
		if (matrix_adj[path->id][path->neighbor->id] == LI_REVERSE)
		{
			matrix_adj[path->neighbor->id][path->id] = LI_CLOSE;
			matrix_adj[path->id][path->neighbor->id] = LI_CLOSE;
		}
		else
			path->out = path->neighbor;
		path = path->neighbor;
	}
}

t_paths			suurballe(t_lem_in *li, int count_required_paths)
{
	t_queue		*queue;
	t_queue		*last;
	t_vertex	*path;
	t_paths		finding;
	int			count_path;

	queue = NULL;
	last = NULL;
	li->start->marked = true;
	count_path = 0;
	while (count_path < count_required_paths &&\
					(path = bfs(queue, li, last)))
	{
		split_vertex(li->matrix_adj, path);
		clean_queue(&queue, &last);
		clean_marked(&li->list_adj[1]);
		++count_path;
	}
	clean_marked(&li->list_adj[1]);
	finding = find_paths(queue, li, last, count_required_paths);
	clean_marked(&li->list_adj[1]);
	clean_queue(&queue, &last);
	desplitted_vertexs(&li->list_adj[1]);
	set_matrix_adj(li->matrix_adj, li->first_link);
	return(finding);
}
