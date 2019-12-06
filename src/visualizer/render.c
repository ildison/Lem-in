/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:33:37 by cormund           #+#    #+#             */
/*   Updated: 2019/11/05 15:38:06 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_visualizer.h"

static void		render_stack_rects(short *stk, t_vis *vis, SDL_Rect rect, int y)
{
	int			i;

	i = 0;
	while (stk[i])
	{
		rect.h = vis->rect.y * stk[i];
		rect.y = y - rect.h;
		SDL_RenderFillRect(vis->ren, &rect);
		++i;
		rect.x += rect.w + vis->between_rect;
	}
}

void			render_rects(t_vis *vis, t_step *stp)
{
	SDL_Rect	rect;

	SDL_SetRenderDrawColor(vis->ren, vis->rect_clr.r, vis->rect_clr.g,\
										vis->rect_clr.b, SDL_ALPHA_OPAQUE);
	rect.w = vis->rect.x;
	rect.x = vis->between_rect;
	if (stp->a)
		render_stack_rects(stp->a, vis, rect, SCREEN_HEIGHT / 2);
	if (stp->b)
		render_stack_rects(stp->b, vis, rect, SCREEN_HEIGHT - 10);
}

void			render_texts(t_vis *vis, t_step *stp)
{
	SDL_RenderCopy(vis->ren, vis->stack_a, NULL, &vis->stack_a_rect);
	SDL_RenderCopy(vis->ren, vis->stack_b, NULL, &vis->stack_b_rect);
	SDL_RenderCopy(vis->ren, stp->oper, NULL, &stp->oper_rect);
}
