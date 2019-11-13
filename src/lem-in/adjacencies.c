/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacencies.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:01 by cormund           #+#    #+#             */
/*   Updated: 2019/11/13 11:41:48 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	id_increment(t_vertex *vertex)
{
	int		count_vertexs;

	count_vertexs = 0;
	while (vertex)
	{
		vertex->id = count_vertexs;
		++count_vertexs;
		vertex = vertex->next;
	}
	return (count_vertexs);
}

static char	**matrix_adj(t_link *link, int count_vertex)
{
	char	**matrix_adj;

	matrix_adj = ft_memalloc_char_2xmas(count_vertex, count_vertex);
	if (!matrix_adj)
		error(strerror(errno));
	while (link)
	{
		matrix_adj[link->vertex_a->id][link->vertex_b->id] = LI_TRUE;
		matrix_adj[link->vertex_b->id][link->vertex_a->id] = LI_TRUE;
		link = link->next;
	}
}

void 		adjacencies(t_lem_in *li)
{
	li->count_vertexs = id_increment(li->start);
	li->matrix_adj = matrix_adj(li->count_vertexs);
}
