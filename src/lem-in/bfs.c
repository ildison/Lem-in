/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:54:03 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/02 11:26:32 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// t_vertex		*bfs(t_queue *queue, t_vertex **list_adj, t_queue *last)
// {
// 	t_vertex	*adj;
// 	int			i;

// 	enqueue(&queue, list_adj[0], &last);
// 	while (queue)
// 	{
// 		adj = queue->vertex; //! если попал на разделенную вершину, то надо идти в сторону родителя
// 		pop_queue(&queue);
// 		if (adj->splited == true && adj->neighbor->splited == false)
// 		{
// 			if (!adj->adj[adj->path_index].vrtx->marked)
// 			{
// 				adj->adj[adj->path_index].vrtx->marked = true;
// 				adj->adj[adj->path_index].vrtx->neighbor = adj;
// 				enqueue(&queue, adj->adj[adj->path_index].vrtx, &last);
// 			}
// 			continue ;
// 		}
// 		i = 0;
// 		while (i < adj->count_edges)
// 		{
// 			if (adj->adj[i].vrtx->type == LI_END && adj->adj[i].status == LI_OPEN)
// 			{
// 				adj->adj[i].vrtx->neighbor = adj;
// 				adj->adj[i].vrtx->adj_index = i;
// 				return (adj->adj[i].vrtx);
// 			}
// 			else if (!adj->adj[i].vrtx->marked && adj->adj[i].status == LI_OPEN)
// 			{
// 				enqueue(&queue, adj->adj[i].vrtx, &last);
// 				adj->adj[i].vrtx->marked = true;
// 				adj->adj[i].vrtx->neighbor = adj;
// 				adj->adj[i].vrtx->adj_index = i;
// 			}
// 			++i;
// 		}
// 	}
// 	return (NULL);
// }

# define LI_COUNT_ADJACENTS vrx->count_edges

// int				is_open_link(t_vertex *src, t_vertex *dst)
// {
// 	int			i;

// 	i = 0;
// 	while (src->adj[i].vrtx != dst)
// 		++i;
// 	return (!src->adj[i].status);
// }

// int				get_adj_index(t_vertex *haystack, t_vertex *needle)
// {
// 	int			i;

// 	i = 0;
// 	while (haystack->adj[i].vrtx != needle)
// 		++i;
// 	return (i);
// }

int				is_open_link(t_lem_in *li, t_vertex *src, t_vertex *dst)
{
	return (li->matrix_adj[src->id][dst->id]);
}

t_vertex		*marked_adjacent(t_queue **queue, t_lem_in *li, t_vertex *vrx, t_queue **last)
{
	int			i;

	i = LI_COUNTER;
	while (++i < LI_COUNT_ADJACENTS)
		if (is_open_link(li, vrx, vrx->adj[i].vrtx) && !vrx->adj[i].vrtx->marked)
		{
			// printf("vrx->name %s | vrx->adj[i].vrtx->name %s\n", vrx->name, vrx->adj[i].vrtx->name);
			vrx->adj[i].vrtx->neighbor = vrx;
			// vrx->adj[i].vrtx->adj_index = i;
			if (vrx->adj[i].vrtx->type == LI_END)
				return (vrx->adj[i].vrtx);
			else
				enqueue(queue, vrx->adj[i].vrtx, last);
			vrx->adj[i].vrtx->marked = true;
		}
	return (NULL);
}


t_vertex		*bfs(t_queue *queue, t_lem_in *li, t_queue *last)
{
	t_vertex	*vrx;

	enqueue(&queue, li->list_adj[0], &last);
	while (queue)
	{
		vrx = pop_queue(&queue);
		if (vrx->splited && is_open_link(li, vrx, vrx->neighbor))
		{
			if (vrx->out->type != LI_START && !vrx->out->marked)
			{
				vrx->out->marked = true;
				vrx->out->neighbor = vrx;
				enqueue(&queue, vrx->out, &last);
			}
		}
		else if ((vrx = marked_adjacent(&queue, li, vrx, &last)))
			return (vrx);
	}
	return (NULL);
}
