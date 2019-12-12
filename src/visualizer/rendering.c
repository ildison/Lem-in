/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 17:08:12 by cormund           #+#    #+#             */
/*   Updated: 2019/12/12 14:24:48 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "li_visualizer.h"

static void		render_egdes(t_vis *vis, t_link *link, SDL_Color **clrs)
{
	SDL_Color	c;

	while (link)
	{
		c = clrs[link->a->id][link->b->id];
		thickLineRGBA(vis->ren, link->a->coord.x, link->a->coord.y, link->b->coord.x, link->b->coord.y, vis->line_width, c.r, c.g, c.b, c.a);
		link = link->next;
	}
}

static void		render_vertexs(t_vis *vis, t_circle *c_vrx, int n_vrx)
{
	SDL_Color	c;
	int			i;

	i = 0;
	while (i < n_vrx)
	{
		c = c_vrx[i].clr;
		filledCircleRGBA(vis->ren, c_vrx[i].x, c_vrx[i].y, vis->radius, c.r, c.g, c.b, c.a);
		++i;
	}
}

void			render_graph(t_vis *vis, t_lem_in *li, t_step *step)
{
	render_egdes(vis, li->first_link, step->m_clrs);
	render_vertexs(vis, step->clr_v, li->count_vertex);
}
