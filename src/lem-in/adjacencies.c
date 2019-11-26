/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacencies.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:01 by cormund           #+#    #+#             */
/*   Updated: 2019/11/26 13:30:26 by vmormont         ###   ########.fr       */
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

	if (!(hash_table = (t_vertex **)ft_memalloc(sizeof(t_vertex *) * (count_vertex + 1))))
		error(LI_ERROR_MALLOC);
	i = 0;
	while (i < count_vertex)
	{
		hash_table[i] = vertex;
		vertex = vertex->next;
		++i;
	}
	return (hash_table);
}

static char			**matrix_adj(t_link *link, int count_vertex)
{
	char			**matrix_adj;

	if (!(matrix_adj = ft_memalloc_char_2xmas(count_vertex, count_vertex)))
		error(LI_ERROR_MALLOC);
	while (link)
	{
		matrix_adj[link->vertex_a->id][link->vertex_b->id] = LI_TRUE;
		matrix_adj[link->vertex_b->id][link->vertex_a->id] = LI_TRUE;
		link = link->next;
	}
	return (matrix_adj);
}

static int			get_count_links(char *links, int count_vertexs)
{
	int				count_links;
	int				i;

	count_links = 0;
	i = 0;
	while (i < count_vertexs)
	{
		count_links += links[i];
		++i;
	}
	return (count_links);
}

static void			get_adjacencies(t_lem_in *li, t_list_adj *adj, char *links)
{
	int				i;

	i = 0;
	while (i < li->count_vertexs)
	{
		if (links[i] == LI_TRUE)
		{
			adj->vrtx = li->hash_table[i];
			++adj;
		}
		++i;
	}
}

static void			list_adj(t_lem_in *li)
{
	t_list_adj		*adj;
	int				count_links;
	int				i;

	i = 0;
	while (i < li->count_vertexs)
	{
		count_links = get_count_links(li->matrix_adj[i], li->count_vertexs);
		if (!(adj = (t_list_adj *)ft_memalloc(sizeof(t_list_adj) * count_links)))
			error(LI_ERROR_MALLOC);
		get_adjacencies(li, adj, li->matrix_adj[i]);
		li->list_adj[i]->count_edges = count_links;
		li->list_adj[i]->adj = adj;
		++i;
	}
}

void 				adjacencies(t_lem_in *li)
{
	li->count_vertexs = id_increment(li->start);
	li->hash_table = hash_table(li->start, li->count_vertexs);
	li->matrix_adj = matrix_adj(li->first_link, li->count_vertexs);
	li->list_adj = li->hash_table;
	list_adj(li);
}
