/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacencies.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:01 by cormund           #+#    #+#             */
/*   Updated: 2019/11/13 15:26:14 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			id_increment(t_vertex *vertex)
{
	int				count_vertexs;

	count_vertexs = 0;
	while (vertex)
	{
		vertex->id = count_vertexs;
		++count_vertexs;
		vertex = vertex->next;
	}
	return (count_vertexs);
}

static t_vertex		**hash_table(t_vertex *vertex, int count_vertex)
{
	t_vertex		**hash_table;
	int				i;

	hash_table = (t_vertex **)ft_memalloc(sizeof(t_vertex *) * (count_vertex + 1));
	if (!hash_table)
		error(strerror(errno));
	i = 0;
	while (i < count_vertex)
	{
		hash_table[i] = vertex;
		vertex = vertex->next;
		++i;
	}
}

static char			**matrix_adj(t_link *link, int count_vertex)
{
	char			**matrix_adj;

	matrix_adj = ft_memalloc_char_2xmas(count_vertex, count_vertex);
	if (!matrix_adj)
		error(strerror(errno));
	while (link)
	{
		matrix_adj[link->vertex_a->id][link->vertex_b->id] = LI_TRUE;
		matrix_adj[link->vertex_b->id][link->vertex_a->id] = LI_TRUE;
		link = link->next;
	}
	return (matrix_adj);
}

static int			get_count_links(char *links)
{
	int				count_links;

	count_links = 0;
	while (*links)
	{
		count_links += *links;
		++links;
	}
}

static void			get_adjacencies(t_vertex **vertex, char *links)
{
	
}

static t_link_adj	*list_adj(t_lem_in *li, char **matrix_adj)
{
	t_link_adj		*link_adj;
	int				count_liks;
	int				i;

	link_adj = (t_link_adj *)malloc(sizeof(t_link_adj) * (li->count_vertexs + 1));
	if (!link_adj)
		error(strerror(errno));
	i = 0;
	while (i < li->count_vertexs)
	{
		count_liks = get_count_links(li->matrix_adj[i]);
		link_adj[i].vertex = li->hash_table[i];
		link_adj[i].adj = ft_memalloc(sizeof(t_vertex *) * (count_liks + 1));
		if (!link_adj[i].adj)
			error(strerror(errno));
		get_adjacencies(link_adj[i].adj, li->matrix_adj[i]);
		++i;
	}
}

void 				adjacencies(t_lem_in *li)
{
	li->count_vertexs = id_increment(li->start);
	li->hash_table = hash_table(li->start, li->count_vertexs);
	li->matrix_adj = matrix_adj(li->first_link, li->count_vertexs);
	li->link_adj = 
}
