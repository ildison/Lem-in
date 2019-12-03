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

// static void		free_lem_in(t_lem_in **li)
// {

// }

int   			main(void)
{
	t_lem_in	*li;
	t_paths		paths;

	li = (t_lem_in *)ft_memalloc(sizeof(t_lem_in));
	if (!li)
		error(strerror(errno));
	read_input(&li->first_line);
	parsing(li);
	adjacencies(li);
	paths = check_paths(li);
	push_ants(li, paths);
	// free_lem_in(li);
	/*
	** FOR BONUS
	*/
	// print_input(li->first_line);
	// print_vertex(li->start);
	// print_links(li->first_link);
	// print_matrix_adj(li->matrix_adj, li->count_vertex);
	// print_list_adj(li->list_adj, li->count_vertex);
	// print_finding(paths);
	return (0);
}
