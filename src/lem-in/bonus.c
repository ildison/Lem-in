/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:55:42 by cormund           #+#    #+#             */
/*   Updated: 2019/12/03 13:15:46 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_input(t_input *in)
{
	while (in)
	{
		ft_putendl(in->line);
		in = in->next;
	}
}

void			print_vertex(t_vertex *vertex)
{
	printf("vertexs:\n\nname => id\n");
	while (vertex)
	{
		printf("%s => %d\n", vertex->name, vertex->id);
		vertex = vertex->next;
	}
}

void			print_links(t_link *link)
{
	printf("\nlinks:\n\n");
	while (link)
	{
		ft_printf("%s - %s\n", link->vertex_a->name, link->vertex_b->name);
		link = link->next;
	}
}

void			print_matrix_adj(char **matrix, int count_vertex)
{
	int			i;
	int			j;

	printf("\nmatrix_adj:\n\n ");
	i = 0;
	while (i < count_vertex)
		printf("  %d", i++);
	j = 0;
	while (j < count_vertex)
	{
		printf("\n%d", j);
		i = 0;
		while (i < count_vertex)
			printf("  %d", matrix[j][i++]);
		++j;
	}
	printf("\n");
}

void			print_list_adj(t_vertex **list_adj, int count_vertex)
{
	int			i;
	int			j;
	t_vertex	**linked;

	printf("\nlist_adj:\n ");
	i = 0;
	while (i < count_vertex)
	{
		printf("\n%d ", list_adj[i]->id);
		linked = list_adj[i]->adj;
		j =  list_adj[i]->count_edges;
		while (j--)
		{
			printf("%d-", (*linked)->id);
			++linked;
		}
		++i;
	}
	printf("\n");
}

void			print_finding(t_paths finding)
{
	t_path		*path;
	int			i;

	printf(".................\n");
	path = finding.path;
	while (path)
	{
		printf("\nlen %d\n\n", path->dist);
		i = 0;
		while (i < path->dist)
		{
			printf("%s ", path->v[i]->name);
			++i;
		}
		printf("\n");
		path = path->next;
	}
	printf("count_paths = %d\n", finding.count_path);
	printf("count steps = %d\n", finding.count_steps);
	printf(".................\n");
}
