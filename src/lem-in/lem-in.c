/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:15:57 by cormund           #+#    #+#             */
/*   Updated: 2019/12/05 17:31:18 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_lem_in(t_lem_in *li, t_paths *paths)
{
	clear_input(li->first_line);
	clear_start(li->start);
	clear_links(li->first_link);
	clear_matrix(li->matrix_adj);
	clear_paths(&paths->path);
	free(li->hash_table);
	free(li);
}

// static int		parse_args(bool *d, bool *v, char **argv, int argc)
// {
// 	static char *opt[] = {"-d", "-v"};
// }

static void		print_usage(void)
{
	ft_printf("\nUASGE: ./lem-in < [map]\n");
	ft_printf("\t-d for debug\n\t-v for visualisation\n");
}

int				main(int argc, char **argv)
{
	t_lem_in	*li;
	t_paths		paths;
	bool		debug;
	bool		visu;

	debug = false;
	visu = false;
	if (!(li = (t_lem_in *)ft_memalloc(sizeof(t_lem_in))))
		error(strerror(errno));
	// if (parse_args(&debug, &visu, argv, argc))
		// print_usage();
	read_input(&li->first_line);
	parsing(li);
	adjacencies(li);
	paths = check_paths(li);
	print_input(li->first_line);
	push_ants(li, paths);
	if (debug == true)
		print_finding(paths);
	free_lem_in(li, &paths);

	// print_matrix_adj(li->matrix_adj, li->count_vertex);
	// print_list_adj(li->list_adj, li->count_vertex);
	/*
	** FOR BONUS
	*/
	// print_vertex(li->start);
	// print_links(li->first_link);
	return (0);
}
