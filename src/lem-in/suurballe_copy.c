/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:05:26 by cormund           #+#    #+#             */
/*   Updated: 2019/11/28 13:58:16 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path			*new_path(t_vertex *adj)
{
	t_path		*new;
	int			i;

	new = ft_memalloc(sizeof(t_path));
	if (!new)
		error(strerror(errno));
	new->dist = adj->dist;
	new->vrtx = (t_vertex **)malloc(sizeof(t_vertex *) * new->dist);
	if (!new->vrtx)
		error(strerror(errno));
	i = adj->dist - 1;
	// printf("\ndist = %d\n", new->dist);
	while (adj->type != LI_START)
	{
		new->vrtx[i] = adj;
		adj = adj->neighbor;
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

t_paths			find_paths(t_queue *queue, t_vertex **list_adj, t_queue *last, int n_path)
{
	t_vertex	*adj;
	t_paths		path;
	t_path		*last_path;
	int			i;

	last_path = NULL;
	ft_bzero(&path, sizeof(t_paths));
	enqueue(&queue, list_adj[0], &last);
	while (queue)
	{
		adj = queue->vertex;
		pop_queue(&queue);
		i = 0;
		while (i < adj->count_edges)
		{
			if (adj->adj[i].vrtx->type == LI_END && adj->adj[i].status == LI_CLOSE)
			{
				adj->adj[i].vrtx->dist = adj->dist + 1;
				adj->adj[i].vrtx->neighbor = adj;
				add_new_path(&path, adj->adj[i].vrtx, &last_path);
				if (!(--n_path))
					return (path);
			}
			else if (!adj->adj[i].vrtx->marked && adj->adj[i].status == LI_CLOSE)
			{
				enqueue(&queue, adj->adj[i].vrtx, &last);
				adj->adj[i].vrtx->marked = true;
				adj->adj[i].vrtx->dist = adj->dist + 1;
				adj->adj[i].vrtx->neighbor = adj;
			}
			++i;
		}
	}
	return (path);
}

void			open_link(t_vertex *vrtx)
{
	int			i;

	i = 0;
	while (i < vrtx->count_edges)
	{
		if (vrtx->adj[i].vrtx == vrtx->neighbor)
		{
			vrtx->adj[i].status = LI_OPEN;
			break ;
		}
		++i;
	}
}

void			split_vertex(t_vertex *path)
{
	printf("--------\n");
	while (path->type != LI_START)
	{
		// if (path->splited == false || path->neighbor->splited == false)
		if (path->neighbor->out != path)
			path->neighbor->adj[path->adj_index].status = LI_CLOSE;
		else
			open_link(path);
		path->out = path->neighbor;
		path->splited = path->type != LI_END ? true : false;
		printf("%s ", path->name);
		path = path->neighbor;
	}
	printf("\n");
	printf("--------\n\n");
}

void			clean_marked(t_vertex **list_adj)
{
	while (*list_adj)
	{
		(*list_adj)->marked = false;
		++list_adj;
	}
}

void			print_finding(t_paths finding)
{
	t_path		*path;
	int			i;

	printf(".................\n");
	path = finding.path;
	while (path)
	{
		i = 0;
		while (i < path->dist)
		{
			printf("%s ", path->vrtx[i]->name);
			++i;
		}
		printf("\n");
		path = path->next;
	}
	printf(".................\n");
}

void			open_links(t_vertex **list_adj)
{
	int			i;

	while (*list_adj)
	{
		i = 0;
		while (i < (*list_adj)->count_edges)
		{
			(*list_adj)->adj[i].status = LI_OPEN;
			++i;
		}
		++list_adj;
	}
}

void			desplitted_vertexs(t_vertex **list_adj)
{
	while (*list_adj)
	{
		(*list_adj)->splited = false;
		++list_adj;
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
		(path = bfs(queue, li->list_adj, last)))
	{
		split_vertex(path);
		clean_queue(&queue, &last);
		clean_marked(&li->list_adj[1]);
		++count_path;
	}
	// printf("count_path(bfs) = %d\n", count_path);
	clean_marked(&li->list_adj[1]);
	finding = find_paths(queue, li->list_adj, last, count_required_paths);
	clean_marked(&li->list_adj[1]);
	desplitted_vertexs(&li->list_adj[1]);
	open_links(li->list_adj);
	print_finding(finding); //? for bonus mb
	return(finding);
}