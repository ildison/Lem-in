/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:15:57 by cormund           #+#    #+#             */
/*   Updated: 2019/11/08 13:17:51 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_input(t_input *in)
{
	while (in)
	{
		ft_putendl(in->line);
		in = in->next;
	}
}

static void		print_vertex(t_vertex *vertex)
{
	printf("vertexs:\n\nname => id\n");
	while (vertex)
	{
		printf("%s => %d\n", vertex->name, vertex->id);
		vertex = vertex->next;
	}
}

static void		print_links(t_link *link)
{
	printf("\nlinks:\n\n");
	while (link)
	{
		ft_printf("%d - %d\n", link->vertex_a->id, link->vertex_b->id);
		link = link->next;
	}
}

static void		print_matrix_adj(char **matrix, int count_vertexs)
{
	int			i;
	int			j;

	printf("\nmatrix_adj:\n\n ");
	i = 0;
	while (i < count_vertexs)
		printf("  %d", i++);
	j = 0;
	while (j < count_vertexs)
	{
		printf("\n%d", j);
		i = 0;
		while (i < count_vertexs)
			printf("  %d", matrix[j][i++]);
		++j;
	}
	printf("\n");
}

static void		print_link_adj(t_link_adj *link_adj, int count_vertexs)
{
	int			i;
	t_vertex	**linked;

	printf("\nlink_adj:\n ");
	i = 0;
	while (i < count_vertexs)
	{
		printf("\n%d ", link_adj[i].vertex->id);
		linked = link_adj[i].adj;
		while (*linked)
		{
			printf("%d-", (*linked)->id);
			++linked;
		}
		++i;
	}
	printf("\n");
}

// static void		free_lem_in(t_lem_in **li)
// {

// }

int   			main(void)
{
	t_lem_in	*li;

	li = (t_lem_in *)ft_memalloc(sizeof(t_lem_in));
	if (!li)
		error(strerror(errno));
	read_input(&li->first_line);
	parsing(li);
	adjacencies(li);
	print_input(li->first_line);

	/*
	** TEST PRINTS
	*/
	print_vertex(li->start);
	print_links(li->first_link);
	print_matrix_adj(li->matrix_adj, li->count_vertexs);
	print_link_adj(li->link_adj, li->count_vertexs);
	// free_lem_in(&li);
	return (0);
}
