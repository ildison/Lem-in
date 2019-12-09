/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collection_steps.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:40:20 by cormund           #+#    #+#             */
/*   Updated: 2019/12/09 17:01:23 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "li_visualizer.h"

t_step		new_step(int count)
{
	t_step	*new;

	new = (t_step *)malloc(t_step);
	if (!new)
		error(strerror(errno));
}

// int			**set_clrs(t_lem_in *li, t_vertex *v)
// {
	
// }

static int	**init_clr_matrix(t_lem_in *li, t_link *link)
{
	int		**clrs;

	clrs = ft_memalloc_int_mas(li->count_vertex, li->count_vertex);
	if (!clrs)
		error(strerror(errno));
	while (link)
	{
		clrs[link->a->id][link->b->id] = CLR_CIRCLE;
		clrs[link->b->id][link->a->id] = CLR_CIRCLE;
		link = link->next;
	}
}

t_step		*collectin_steps(t_vis *vis, t_lem_in *li, t_paths srbl_paths, t_paths res_paths)
{
	t_step	*first_step;
	t_step	*last_step;

	first_step = new_step(li->count_vertex);
	last_step = first_step;
	first_step->clrs = init_clr_matrix(li, li->first_link);
	return (first_step);
}
