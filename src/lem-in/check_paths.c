/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 14:32:25 by cormund           #+#    #+#             */
/*   Updated: 2019/12/03 13:41:06 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths		check_paths(t_lem_in *li)
{
	t_paths	best_paths;
	t_paths	new_paths;
	int		count_required_paths;

	best_paths = suurballe(li, 1);
	if (best_paths.count_path == 0)
		error(LI_ERROR_NO_PATH_FROM_START_TO_END);
	best_paths.count_steps = count_steps_and_ants(best_paths, li->count_ants);
	count_required_paths = 2;
	while (count_required_paths < li->count_ants)
	{
		new_paths = suurballe(li, count_required_paths);
		new_paths.count_steps = count_steps_and_ants(new_paths, li->count_ants);
		if (new_paths.count_path < count_required_paths ||\
						new_paths.count_steps > best_paths.count_steps)
		{
			// free_paths(new_paths);
			break ;
		}
		if (new_paths.count_steps < best_paths.count_steps)
		{
			best_paths = new_paths;
			// free_paths(new_paths);
		}
		// free_paths(new_paths);
		++count_required_paths;
	}
	return (best_paths);
}
