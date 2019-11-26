/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 14:32:25 by cormund           #+#    #+#             */
/*   Updated: 2019/11/26 10:47:02 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			init_dist(int *dist, t_paths finding)
{
	t_path		*path;
	int			i;

	path = finding.path;
	i = 0;
	while (i < finding.count_path)
	{
		dist[i] = path->dist;
		path = path->next;
		i++;
	}
	// ft_printf("Exit from init_dist\n");
}

void		count_ants_for_paths(int *dist, t_path *path)
{
	int		i;

	i = 0;
	while (path)
	{
		path->ants = dist[i] - path->dist;
		// printf("path->ants = %d\n", path->ants);
		++i;
		path = path->next;
	}
}

int			count_steps_for_paths(t_paths paths, int count_ants)
{
	int		dist_increment[paths.count_path + 1];
	int		max_use_index;
	int		i;

	init_dist(dist_increment, paths);
	dist_increment[paths.count_path] = INT_MAX;
	max_use_index = 0;
	// printf("dist_increment[1] = %d\n", dist_increment[1]);
	while (count_ants)
	{
		while (dist_increment[max_use_index] >= dist_increment[max_use_index + 1])
			++max_use_index;
		i = 0;
		while (i <= max_use_index && count_ants)
		{
			++dist_increment[i];
			++i;
			--count_ants;
		}
	}
	count_ants_for_paths(dist_increment, paths.path);
	return (dist_increment[0] - 1);
}

t_paths		check_paths(t_lem_in *li)
{
	t_paths	best_paths;
	t_paths	new_paths;
	int		count_steps;
	int		count_required_paths;

	best_paths = suurballe(li, 1);
	if (best_paths.count_path == 0)
		error(LI_ERROR_NO_PATH_FROM_START_TO_END);
	best_paths.count_steps = count_steps_for_paths(best_paths, li->count_ants);
	// printf("count_steps = %d\n", best_paths.count_steps);
	count_required_paths = 2;
	while (count_required_paths < li->count_ants)
	{
		// ft_printf("Check suurballe count_required_paths = %i, li->count_ants = %i\n", count_required_paths, li->count_ants);
		new_paths = suurballe(li, count_required_paths);
		count_steps = count_steps_for_paths(new_paths, li->count_ants);
		if (new_paths.count_path < count_required_paths ||\
						count_steps > best_paths.count_steps)
		{
			// free_paths(new_paths);
			break ;
		}
		if (count_steps < best_paths.count_steps)
		{
			best_paths = new_paths;
			best_paths.count_steps = count_steps;
			// free_paths(new_paths);
			// best_paths = new_best(new_paths, count_steps);
		}
		// free_paths(new_paths);
		++count_required_paths;
	}
	// ft_printf("Exit from check_path\n");
	return (best_paths);
}
