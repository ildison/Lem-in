/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:02:47 by cormund           #+#    #+#             */
/*   Updated: 2019/12/06 17:06:24 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "li_visualizer.h"

static void		events(t_vis *vis)
{
	if (SDL_EVENT == SDL_QUIT || SDL_KEYSTATE[SDL_ESCAPE])
		vis->quit = SDL_TRUE;
	else if (SDL_EVENT == SDL_KEYDOWN && SDL_KEYSTATE[SDL_SPACE])
		vis->pause ^= SDL_TRUE;
	// else if (vis->pause && SDL_EVENT == SDL_KEYDOWN &&\
	// 		SDL_KEYSTATE[SDL_RIGHT] && *step && (*step)->next)
	// 	*step = (*step)->next;
	// else if (vis->pause && SDL_EVENT == SDL_KEYDOWN &&\
	// 		SDL_KEYSTATE[SDL_LEFT] && *step && (*step)->prev)
	// 	*step = (*step)->prev;
	else if (SDL_EVENT == SDL_KEYDOWN && SDL_KEYSTATE[SDL_UP] &&\
													vis->delay < 100)
		++vis->delay;
	else if (SDL_EVENT == SDL_KEYDOWN && SDL_KEYSTATE[SDL_DOWN] &&\
													vis->delay > 0)
		--vis->delay;
	// else if (SDL_EVENT == SDL_KEYDOWN && SDL_KEYSTATE[SDL_R])
	// 	*step = vis->first_step;
}

void fill_circle(t_vis *vis, int cx, int cy, int radius)
{
	for (double dy = 1; dy <= radius; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		// int x = cx - dx;
		SDL_SetRenderDrawColor(vis->ren, vis->rect_clr.r, vis->rect_clr.g, vis->rect_clr.b, 0);
		SDL_RenderDrawLine(vis->ren, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
		SDL_RenderDrawLine(vis->ren, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
	}
}

static void		render_update(t_vis *vis)
{
	// SDL_Texture	*tex;
	// SDL_Surface	*surf;

	SDL_SetRenderDrawColor(vis->ren, vis->bgrnd_clr.r, vis->bgrnd_clr.g,\
										vis->bgrnd_clr.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(vis->ren);
	// render_rects(vis, step);
	// render_texts(vis, step);
	fill_circle(vis, 1000, 1000, 500);
	// tex = SDL_CreateTextureFromSurface(vis->ren, surf);
	// SDL_FreeSurface(surf);
	SDL_RenderPresent(vis->ren);
}

void			loop(t_vis *vis, t_lem_in *li)
{
	// t_step		*step;
	int			delay;

	// step = new_step(chkr, vis, ft_strdup(FIRST_STEP));
	li = 0; //!delete
	vis->delay = 10;
	delay = vis->delay;
	while (!vis->quit)
	{
		SDL_Delay(2);
		while (SDL_PollEvent(&vis->e))
			events(vis);
		render_update(vis);
		// if (!vis->pause && !delay)
		// 	step = next_step(vis, step, chkr);
		delay += delay ? -1 : vis->delay;
	}
}
