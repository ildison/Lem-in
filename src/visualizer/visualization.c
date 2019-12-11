/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:40:31 by cormund           #+#    #+#             */
/*   Updated: 2019/12/11 18:30:17 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "li_visualizer.h"

// static void	cleaning_up(t_vis *vis, t_step *stp)
// {
// 	t_step	*tmp;

// 	while (stp)
// 	{
// 		free(stp->a);
// 		free(stp->b);
// 		SDL_DestroyTexture(stp->oper);
// 		tmp = stp;
// 		stp = stp->next;
// 		free(tmp);
// 	}
// 	SDL_DestroyTexture(vis->stack_a);
// 	SDL_DestroyTexture(vis->stack_b);
// 	free(vis);
// }

static void	destroy_init(t_vis *vis)
{
	// TTF_CloseFont(vis->font_text);
	SDL_DestroyRenderer(vis->ren);
	SDL_DestroyWindow(vis->win);
	TTF_Quit();
	SDL_Quit();
}

// static void	open_font(t_vis *vis)
// {
// 	vis->font_text = TTF_OpenFont("/src/visualizer/font/FuturaPT-Light.ttf",\
// 																		20);
// 	if (!vis->font_text)
// 		error(TTF_GetError());
// }

static void	init(t_vis *vis)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		error(SDL_GetError());
	if (TTF_Init() < 0)
		error(TTF_GetError());
	vis->win = SDL_CreateWindow("Lem-in visualizer", SDL_WINDOWPOS_CENTERED,\
	SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!vis->win)
		error(TTF_GetError());
	if (!(vis->ren = SDL_CreateRenderer(vis->win, -1, 0)))
		error(TTF_GetError());
	// open_font(vis);
	vis->keystate = SDL_GetKeyboardState(NULL);
	vis->delay = 40;
}

void		visualizer(t_lem_in *li, int count_paths)
{
	t_vis	*vis;

	li->visu = true;
	if (!(vis = ft_memalloc(sizeof(t_vis))))
		error(strerror(errno));
	init(vis);
	background(vis, li);
	vis->srbll = ft_memalloc(sizeof(t_paths));
	if (!vis->srbll)
		error(strerror(errno));
	vis->paths = suurballe(li, count_paths, vis->srbll);
	vis->first_step = collection_steps(vis, li, NULL);
	loop(vis, li, vis->first_step);
	destroy_init(vis);
	// cleaning_up(vis, vis->first_step);
}
