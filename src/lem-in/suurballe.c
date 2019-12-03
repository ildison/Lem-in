/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:05:26 by cormund           #+#    #+#             */
/*   Updated: 2019/12/03 13:14:27 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path			*new_path(t_vertex *vrx)
{
	t_path		*new;
	int			i;

	new = ft_memalloc(sizeof(t_path));
	if (!new)
		error(strerror(errno));
	new->dist = vrx->dist;
	new->v = (t_vertex **)malloc(sizeof(t_vertex *) * new->dist);
	if (!new->v)
		error(strerror(errno));
	i = vrx->dist - 1;
	// printf("\ndist = %d\n", new->dist);
	while (vrx->type != LI_START)
	{
		new->v[i] = vrx;
		vrx = vrx->neighbor;
		--i;
	}
	return (new);
}

void			add_new_path(t_paths *paths, t_vertex *adj, t_path **last_path)
{
	t_path		*new;

	new = new_path(adj);
	if (*last_path)
		(*last_path)->next = new;
	else
		paths->path = new;
	*last_path = new;
	++paths->count_path;
}

void			clean_marked(t_vertex **list_adj)
{
	while (*list_adj)
	{
		(*list_adj)->marked = false;
		++list_adj;
	}
}

void			desplitted_vertexs(t_vertex **list_adj)
{
	while (*list_adj)
	{
		(*list_adj)->splited = false;
		(*list_adj)->out = NULL;
		(*list_adj)->neighbor = NULL;
		++list_adj;
	}

}

t_paths			find_paths(t_queue *queue, t_lem_in *li, t_queue *last, int n_path)
{
	t_vertex	*vrx;
	t_paths		path;
	t_path		*last_path;
	int			i;

	last_path = NULL;
	ft_bzero(&path, sizeof(t_paths));
	enqueue(&queue, li->list_adj[0], &last);
	while (queue)
	{
		vrx = pop_queue(&queue);
		i = LI_COUNTER;
		while (++i < vrx->count_edges)
			if (is_open_link(li, vrx, vrx->adj[i]) == -1  && !vrx->adj[i]->marked)
			{
				vrx->adj[i]->dist = vrx->dist + 1;
				vrx->adj[i]->neighbor = vrx;
				if (vrx->adj[i]->type == LI_END)
				{
					add_new_path(&path, vrx->adj[i], &last_path);
					if (!(--n_path))
						return (path);
				}
				else
				{
					enqueue(&queue, vrx->adj[i], &last);
					vrx->adj[i]->marked = true;
				}
			}
	}
	return (path);
}

void			split_vertex(t_lem_in *li, t_vertex *path)
{
	// printf("--------\n");
	while (path->type != LI_START)
	{
		li->matrix_adj[path->neighbor->id][path->id] = -1;
		path->splited = path->type != LI_END ? true : false;
		if (li->matrix_adj[path->id][path->neighbor->id] == -1)
		{
			li->matrix_adj[path->neighbor->id][path->id] = 0;
			li->matrix_adj[path->id][path->neighbor->id] = 0;
		}
		else
			path->out = path->neighbor;
		// printf("%s ", path->name);
		path = path->neighbor;
	}
	// printf("\n");
	// printf("--------\n\n");
}

t_paths			suurballe(t_lem_in *li, int count_required_paths)
{
	// static int	count_here = 1;

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
	// printf("HERE(%d)\n", count_here++);
		split_vertex(li, path);
		clean_queue(&queue, &last);
		clean_marked(&li->list_adj[1]);
		++count_path;
	}
	// count_here = 1;
	// printf("count_path(bfs) = %d\n", count_path);
	clean_marked(&li->list_adj[1]);
	finding = find_paths(queue, li, last, count_required_paths);
	// print_finding(finding);
	clean_marked(&li->list_adj[1]);
	clean_queue(&queue, &last);
	desplitted_vertexs(&li->list_adj[1]);
	matrix_adj(li->matrix_adj, li->first_link);
	return(finding);
}
