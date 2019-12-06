/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:15:57 by cormund           #+#    #+#             */
/*   Updated: 2019/12/06 11:56:40 by cormund          ###   ########.fr       */
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

static int		get_option(char ac, char **av, char *option)
{
	int			i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if (!ft_strcmp(&av[i][1], option))
				return (i);
			++i;
		}
		else
			break ;
	}
	return (0);
}

static int		check_valid_options(int ac, char **av, char **opt, int opt_num)
{
	int			i;
	int			j;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			j = 0;
			while (j < opt_num)
			{
				if (!ft_strcmp(&av[i][1], opt[j]))
					break ;
				++j;
			}
			if (j == opt_num)
				return (0);
		}
		++i;
	}
	return (1);
}

static void		parse_args(bool *d, bool *v, char **argv, int argc)
{
	static char *opt[] = {"d", "v", "debug", "visu"};

	if (argc > 1 && !check_valid_options(argc, argv, opt, 4))
		error("UASGE: ./lem-in < [map]\n\t-d for \
debug\n\t-v for visualisation\n");
	if (get_option(argc, argv, "d") > 0)
		*d = true;
	else if (get_option(argc, argv, "debug") > 0)
		*d = true;
	if (get_option(argc, argv, "v") > 0)
		*v = true;
	else if (get_option(argc, argv, "visu") > 0)
		*v = true;
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
	parse_args(&debug, &visu, argv, argc);
	read_input(&li->first_line);
	parsing(li);
	adjacencies(li);
	paths = check_paths(li);
	print_input(li->first_line);
	if (debug == true)
		print_finding(paths);
	else
		push_ants(li, paths);
	/*
	** print_list_adj(li->list_adj, li->count_vertex);
	** print_matrix_adj(li->matrix_adj, li->count_vertex);
	*/
	free_lem_in(li, &paths);
	return (0);
}
