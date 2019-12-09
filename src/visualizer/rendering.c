/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 17:08:12 by cormund           #+#    #+#             */
/*   Updated: 2019/12/09 19:18:05 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "li_visualizer.h"

void			render_egdes(t_vis *vis, t_link *link, SDL_Color **clrs)
{
	SDL_Color	c;

	while (link)
	{
		c = clrs[link->a->id][link->b->id];
		thickLineRGBA(vis->ren, link->a->coord.x, link->a->coord.y, link->b->coord.x, link->b->coord.y, vis->radius, c.r, c.g, c.b, 255);
		link = link->next;
	}
}

void			render_vertexs(t_vis *vis, t_clr_v *c_vrx, int n_vrx)
{
	SDL_Color	c;
	int			i;

	i = 0;
	while (i < n_vrx)
	{
		c = c_vrx[i].clr;
		filledCircleRGBA(vis->ren, c_vrx[i].v->coord.x, c_vrx[i].v->coord.y, vis->radius, c.r, c.g, c.b, 255);
		++i;
	}
}

void			render_graph(t_vis *vis, t_lem_in *li, t_step *step)
{
	render_egdes(vis, li->first_link, step->clrs);
	render_vertexs(vis, step->clr_v, li->count_vertex);
}
