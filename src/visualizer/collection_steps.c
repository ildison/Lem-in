/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collection_steps.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:40:20 by cormund           #+#    #+#             */
/*   Updated: 2019/12/11 11:50:58 by cormund          ###   ########.fr       */
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

	clr_v = (t_clr_v *)ft_memalloc(sizeof(t_clr_v) * li->count_vertex);
	if (!clr_v)
		error(strerror(errno));
	i = 0;
	while (i < li->count_vertex)
	{
		clr_v[i].v = li->list_adj[i];
		clr_v[i].clr = cpy_v ? cpy_v[i].clr : get_color(CLR_CIRCLE);
		++i;
	}
	return (clr_v);
}

void			add_color(t_step *step, t_path *path, int index, SDL_Color clr)
{
	if (index)
	{
		if (path->edge[index])
		{
			step->m_clrs[path->v[index]->id][path->v[index - 1]->id] = clr;
			step->m_clrs[path->v[index - 1]->id][path->v[index]->id] = clr;
		}
		else
		{
			step->m_clrs[path->v[index]->id][path->v[index - 1]->id] = get_color(CLR_BLACK);
			step->m_clrs[path->v[index - 1]->id][path->v[index]->id] = get_color(CLR_BLACK);
		}
	}
	else
	{
		step->m_clrs[path->v[index]->id][0] = clr;
		step->m_clrs[0][path->v[index]->id] = clr;
	}
	if (step->clr_v[path->v[index]->id].v->type != LI_END)
		step->clr_v[path->v[index]->id].clr = clr;
}

t_step			*collect_srbll_paths(t_vis *vis, t_step *step, t_lem_in *li, t_paths paths)
{
	t_path		*path;
	int			n_path;
	int			n_v;
	int			n_clr;

	path = paths.path;
	n_path = 0;
	n_clr = 0;
	while (n_path < paths.count_path)
	{
		n_v = LI_COUNTER;
		while (++n_v < path->dist)
		{
			step->next = new_step();
			step->next->m_clrs = init_matrix_clr(step->m_clrs, li->count_vertex, li->first_link);
			step->next->clr_v = init_vertex_clr(step->clr_v, li);
			add_color(step->next, path, n_v, vis->colors[n_path]);
			step->next->prev = step;
			step = step->next;
		}
		path = path->next;
		n_clr += n_clr < 19 ? 1 : -COUNT_COLORS;
		++n_path;
	}
	return (step);
}

t_step			*turn_off_unused_paths(t_step *step, t_lem_in *li, t_link *link)
{
	step->next = new_step();
	step->next->clr_v = init_vertex_clr(NULL, li);
	step->next->m_clrs = init_matrix_clr(step->m_clrs, li->count_vertex, link);
	step->next->prev = step;
	step = step->next;
	while (link)
	{
		if (step->prev->m_clrs[link->a->id][link->b->id].r == get_color(CLR_CIRCLE).r)
			step->m_clrs[link->a->id][link->b->id] = get_color(CLR_BLACK);
		else if (step->prev->m_clrs[link->a->id][link->b->id].r != get_color(CLR_BLACK).r)
			step->m_clrs[link->a->id][link->b->id] = get_color(CLR_CIRCLE);
		link = link->next;
	}
	return (step);
}

t_step			*collect_final_paths(t_vis *vis, t_step *step, t_lem_in *li, t_paths paths)
{
	t_path		*path;
	int			n_path;
	int			n_v;
	int			n_clr;

	path = paths.path;
	n_path = 0;
	n_clr = COUNT_COLORS;
	while (n_path < paths.count_path)
	{
		step->next = new_step();
		step->next->m_clrs = init_matrix_clr(step->m_clrs, li->count_vertex, li->first_link);
		step->next->clr_v = init_vertex_clr(step->clr_v, li);
		step->next->prev = step;
		step = step->next;
		n_v = LI_COUNTER;
		while (++n_v < path->dist)
			add_color(step, path, n_v, vis->colors[n_clr]);
		n_clr += n_clr != 0 ? -1 : COUNT_COLORS;
		path = path->next;
		++n_path;
	}
	return (step);
}

t_step			*collection_steps(t_vis *vis, t_lem_in *li, t_paths srbl_paths, t_paths res_paths)
{
	t_step		*step;
	t_step		*last_step;

	step = new_step();
	step->m_clrs = init_matrix_clr(NULL, li->count_vertex, li->first_link);
	step->clr_v = init_vertex_clr(NULL, li);
	last_step = collect_srbll_paths(vis, step, li, srbl_paths);
	last_step = turn_off_unused_paths(last_step, li, li->first_link);
	last_step = collect_final_paths(vis, last_step, li, res_paths);
	last_step->fin = SDL_TRUE;
	return (step);
}
