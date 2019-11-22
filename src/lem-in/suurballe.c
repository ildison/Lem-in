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
		adj = queue->vertex; //! если попал на разделенную вершину, то надо идти в сторону родителя
		pop_queue(&queue);
		if (adj->splited == true && adj->neighbor->splited == false)
		{
			if (!adj->adj[adj->path_index].vrtx->marked)
			{
				adj->adj[adj->path_index].vrtx->marked = true;
				adj->adj[adj->path_index].vrtx->neighbor = adj;
				enqueue(&queue, adj->adj[adj->path_index].vrtx, &last);
			}
			continue ;
		}
		i = 0;
		while (i < adj->count_edges)
		{
			if (adj->adj[i].vrtx->type == LI_END && adj->adj[i].status == LI_OPEN)
			{
				adj->adj[i].vrtx->neighbor = adj;
				adj->adj[i].vrtx->adj_index = i;
				return (adj->adj[i].vrtx);
			}
			else if (!adj->adj[i].vrtx->marked && adj->adj[i].status == LI_OPEN)
			{
				enqueue(&queue, adj->adj[i].vrtx, &last);
				adj->adj[i].vrtx->marked = true;
				// adj->adj[i].vrtx->dist = adj->dist + 1;
				adj->adj[i].vrtx->neighbor = adj;
				adj->adj[i].vrtx->adj_index = i;
			}
			++i;
		}
	}
	return (NULL);
}

t_path			*new_path(t_vertex *adj)
{
	t_path		*new;
	int			i;

	new = ft_memalloc(sizeof(t_path));
	if (!new)
		error(strerror(errno));
	new->dist = adj->dist + 1;
	new->vrtx = (t_vertex **)malloc(sizeof(t_vertex *) * new->dist);
	if (!new->vrtx)
		error(strerror(errno));
	i = adj->dist - 1;
	printf("\ndist = %d\n", i);
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
				--n_path;
				add_new_path(&path, adj, &last_path);
				if (!n_path)
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
	while (path->type != LI_START)
	{
		// close_link(path);
		path->neighbor->adj[path->adj_index].status = LI_CLOSE;
		path->path_index = path->adj_index;
		open_link(path);
		path->splited = path->type != LI_END ? true : false;
		// printf("%s ", path->name);
		path = path->neighbor;
	}
	// printf("\n");
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

	path = finding.path;
	while (path)
	{
		i = 0;
		while (i < path->dist - 1)
		{
			printf("%s ", path->vrtx[i]->name);
			++i;
		}
		printf("\n");
		path = path->next;
	}
}

void			suurballe(t_lem_in *li)
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
	while (count_path < 1 && (path = bfs(queue, li->list_adj, last))) //? count_path < 2 only for test
	{
		split_vertex(path);
		clean_queue(&queue, &last);
		clean_marked(&li->list_adj[1]);
		++count_path;
	}
	finding = find_paths(queue, li->list_adj, last, 1); //? 2 is count_path
	clean_marked(&li->list_adj[1]);
	print_finding(finding); //? for bonus mb
}
