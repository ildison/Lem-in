/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacencies.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:01 by cormund           #+#    #+#             */
/*   Updated: 2019/11/14 21:17:51 by vmormont         ###   ########.fr       */
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
	return (hash_table);
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

static void			get_adjacencies(t_lem_in *li, t_vertex **vertex, char *links)
{
	int				i;

	i = 0;
	while (i < li->count_vertexs)
	{
		if (links[i] == LI_TRUE)
		{
			*vertex = li->hash_table[i];
			++vertex;
		}
		++i;
	}
}

static t_link_adj	*list_adj(t_lem_in *li)
{
	t_link_adj		*link_adj;
	int				count_links;
	int				i;

	link_adj = (t_link_adj *)malloc(sizeof(t_link_adj) * (li->count_vertexs));
	if (!link_adj)
		error(strerror(errno));
	i = 0;
	while (i < li->count_vertexs)
	{
		count_links = get_count_links(li->matrix_adj[i], li->count_vertexs);
		link_adj[i].vertex = li->hash_table[i];
		link_adj[i].vertex->count_edges = count_links;
		link_adj[i].adj = ft_memalloc(sizeof(t_vertex *) * (count_links + 1));
		if (!link_adj[i].adj)
			error(strerror(errno));
		get_adjacencies(li, link_adj[i].adj, li->matrix_adj[i]);
		++i;
	}
	return (link_adj);
}

void 				adjacencies(t_lem_in *li)
{
	li->count_vertexs = id_increment(li->start);
	li->hash_table = hash_table(li->start, li->count_vertexs);
	li->matrix_adj = matrix_adj(li->first_link, li->count_vertexs);
	li->link_adj = list_adj(li);
}
