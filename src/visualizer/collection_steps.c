/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collection_steps.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:40:20 by cormund           #+#    #+#             */
/*   Updated: 2019/12/11 11:59:23 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "li_visualizer.h"

t_step			*new_step()
{
	t_step		*new;

	new = (t_step *)ft_memalloc(sizeof(t_step));
	if (!new)
		error(strerror(errno));
	return (new);
}

SDL_Color		**init_matrix_clr(SDL_Color **m_cpy, int n_v, t_link *link)
{
	SDL_Color	**m_clr;

	m_clr = (SDL_Color **)ft_memalloc_int_mas(n_v, n_v);
	if (!m_clr)
		error(strerror(errno));
	if (m_cpy)
		while (link)
		{
			m_clr[link->a->id][link->b->id] = m_cpy[link->a->id][link->b->id];
			link = link->next;
		}
	else
		while (link)
		{
			m_clr[link->a->id][link->b->id] = get_color(CLR_CIRCLE);
			link = link->next;
		}
	return (m_clr);
}

t_clr_v			*init_vertex_clr(t_clr_v *cpy_v, t_lem_in *li)
{
	t_clr_v		*clr_v;
	int			i;

	clr_v = (t_clr_v *)ft_memalloc(sizeof(t_clr_v) * LI_COUNT_VRTX);
	if (!clr_v)
		error(strerror(errno));
	i = 0;
	while (i < LI_COUNT_VRTX)
	{
		clr_v[i].v = li->list_adj[i];
		clr_v[i].clr = cpy_v ? cpy_v[i].clr : get_color(CLR_CIRCLE);
		++i;
	}
	return (clr_v);
}

t_step			*collection_steps(t_vis *vis, t_lem_in *li, t_paths srbl_paths, t_paths res_paths)
{
	t_step		*step;
	t_step		*last_step;

	step = new_step();
	step->m_clrs = init_matrix_clr(NULL, LI_COUNT_VRTX, li->first_link);
	step->clr_v = init_vertex_clr(NULL, li);
	last_step = collect_srbll_paths(vis, step, li, srbl_paths);
	last_step = turn_off_unused_paths(last_step, li, li->first_link);
	last_step = collect_final_paths(vis, last_step, li, res_paths);
	last_step->fin = SDL_TRUE;
	return (step);
}
