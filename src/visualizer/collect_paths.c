/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:58:57 by cormund           #+#    #+#             */
/*   Updated: 2019/12/11 17:33:30 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "li_visualizer.h"

static void		add_color(t_step *step, t_path *path, int index, SDL_Color clr)
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
			step->m_clrs[path->v[index]->id][path->v[index - 1]->id] =\
													get_color(CLR_BLACK);
			step->m_clrs[path->v[index - 1]->id][path->v[index]->id] =\
													get_color(CLR_BLACK);
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

t_step			*collect_srbll_paths(t_vis *vis, t_step *step, t_lem_in *li,\
																t_paths *paths)
{
	t_path		*path;
	int			n_path;
	int			n_v;
	int			n_clr;

	path = paths->path;
	n_path = 0;
	n_clr = 0;
	while (n_path < paths->count_path)
	{
		n_v = LI_COUNTER;
		while (++n_v < path->dist)
		{
			step->next = new_step();
			step->next->m_clrs = init_matrix_clr(step->m_clrs, LI_COUNT_VRTX,\
																li->first_link);
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
	step->next->m_clrs = init_matrix_clr(step->m_clrs, LI_COUNT_VRTX, link);
	step->next->prev = step;
	step = step->next;
	while (link)
	{
		if (step->prev->m_clrs[link->a->id][link->b->id].r ==\
												get_color(CLR_CIRCLE).r)
			step->m_clrs[link->a->id][link->b->id] = get_color(CLR_BLACK);
		else if (step->prev->m_clrs[link->a->id][link->b->id].r !=\
											get_color(CLR_BLACK).r)
			step->m_clrs[link->a->id][link->b->id] = get_color(CLR_CIRCLE);
		link = link->next;
	}
	return (step);
}

t_step			*collect_final_paths(t_vis *vis, t_step *step, t_lem_in *li,\
																t_paths *paths)
{
	t_path		*path;
	int			n_path;
	int			n_v;
	int			n_clr;

	path = paths->path;
	n_path = 0;
	n_clr = COUNT_COLORS;
	while (n_path < paths->count_path)
	{
		step->next = new_step();
		step->next->m_clrs = init_matrix_clr(step->m_clrs, LI_COUNT_VRTX,\
															li->first_link);
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
