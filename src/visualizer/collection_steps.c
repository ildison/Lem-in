/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collection_steps.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:40:20 by cormund           #+#    #+#             */
/*   Updated: 2019/12/09 19:15:13 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "li_visualizer.h"

t_step				*new_step()
{
	t_step			*new;

	new = (t_step *)malloc(sizeof(t_step));
	if (!new)
		error(strerror(errno));
	return (new);
}

// int			**set_clrs(t_lem_in *li, t_vertex *v)
// {
	
// }

static SDL_Color	**init_clr_matrix(t_lem_in *li, t_link *link)
{
	SDL_Color		**clrs;

	clrs = (SDL_Color **)ft_memalloc_int_mas(li->count_vertex, li->count_vertex);
	if (!clrs)
		error(strerror(errno));
	while (link)
	{
		clrs[link->a->id][link->b->id] = get_color(CLR_CIRCLE);
		clrs[link->b->id][link->a->id] = get_color(CLR_CIRCLE);
		link = link->next;
	}
	return (clrs);
}

t_clr_v				*init_vertex_clr(t_lem_in *li)
{
	t_clr_v			*clr_v;
	int				i;

	i = 0;
	clr_v = (t_clr_v *)ft_memalloc(sizeof(t_clr_v) * li->count_vertex);
	if (!clr_v)
		error(strerror(errno));
	while (i < li->count_vertex)
	{
		clr_v[i].v = li->list_adj[i];
		clr_v[i].clr = get_color(CLR_CIRCLE);
		++i;
	}
	return (clr_v);
}

t_step				*collection_steps(t_vis *vis, t_lem_in *li, t_paths srbl_paths, t_paths res_paths)
{
	t_step			*first_step;
	t_step			*last_step;

srbl_paths = res_paths;//!delete
res_paths = srbl_paths;//!delete
vis->pause = 0;//!delete
	first_step = new_step();
	last_step = first_step;
	first_step->clrs = init_clr_matrix(li, li->first_link);
	first_step->clr_v = init_vertex_clr(li);
	return (first_step);
}
