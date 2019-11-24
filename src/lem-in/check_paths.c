/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 14:32:25 by cormund           #+#    #+#             */
/*   Updated: 2019/11/24 16:41:34 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			count_steps_for_paths(t_paths paths, int count_ants)
{
	int		*dist_increment;
	int		max_use_index;
	int		i;

	if (!(dist_increment = ft_memalloc(sizeof(int) * paths.count_path + 1)))
		error(strerror(errno));
	dist_increment[paths.count_path] = INT_MAX;
	i = 0;
	while (paths.path)
	{
		dist_increment[i] = paths.path->dist;
		paths.path = paths.path->next;
		++i;
	}
	max_use_index = 0;
	while (count_ants)
	{
		while (dist_increment[max_use_index] >= dist_increment[max_use_index + 1])
			++max_use_index;
		i = 0;
		while (i <= max_use_index && count_ants--)
		{
			++dist_increment[i];
			++i;
		}
	}
	free(dist_increment);
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
	printf("count_steps = %d\n", best_paths.count_steps);
	count_required_paths = 2;
	while (count_required_paths < li->count_ants)
	{
		new_paths = suurballe(li, count_required_paths);
		count_steps = count_steps_for_paths(new_paths, li->count_ants);
		printf("count_steps = %d\n", count_steps);
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
	return (best_paths);
}
