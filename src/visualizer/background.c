/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:33:51 by cormund           #+#    #+#             */
/*   Updated: 2019/12/06 16:14:35 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "li_visualizer.h"

// SDL_Texture		*create_texture(TTF_Font *font, char *text, SDL_Renderer *ren,\
// 															SDL_Color color)
// {
// 	SDL_Texture	*tex;
// 	SDL_Surface	*surf;

// 	surf = TTF_RenderText_Blended(font, text, color);
// 	tex = SDL_CreateTextureFromSurface(ren, surf);
// 	SDL_FreeSurface(surf);
// 	return (tex);
// }

SDL_Color		get_color(int clr)
{
	SDL_Color	color;

	color.r = clr >> 16;
	color.g = (clr >> 8) & 0xff;
	color.b = clr & 0xff;
	color.a = 0xff;
	return (color);
}

// void			rect_size(t_vis *vis, t_checker *chkr)
// {
// 	int			count_rects;
// 	int			wigth;

// 	count_rects = size_stack(chkr->a);
// 	wigth = SCREEN_WIDTH / count_rects;
// 	vis->between_rect = wigth / 2;
// 	vis->rect.x = wigth - vis->between_rect;
// 	if (vis->rect.x > 20)
// 	{
// 		vis->rect.x = 20;
// 		vis->between_rect = 20;
// 	}
// 	vis->rect.y = (SCREEN_HEIGHT / 2 - 40) / count_rects;
// }

// void			text(t_vis *vis)
// {
// 	TTF_SizeText(vis->font_text, "Stack a", &vis->stack_a_rect.w,\
// 												&vis->stack_a_rect.h);
// 	vis->stack_a_rect.x = 10;
// 	vis->stack_a_rect.y = 10;
// 	vis->stack_a = create_texture(vis->font_text, "Stack a", vis->ren,\
// 															vis->text_clr);
// 	vis->stack_b_rect.w = vis->stack_a_rect.w;
// 	vis->stack_b_rect.h = vis->stack_a_rect.h;
// 	vis->stack_b_rect.x = vis->stack_a_rect.x;
// 	vis->stack_b_rect.y = vis->stack_a_rect.y + SCREEN_HEIGHT / 2;
// 	vis->stack_b = create_texture(vis->font_text, "Stack b", vis->ren,\
// 															vis->text_clr);
// 	vis->oper_sz.y = SCREEN_HEIGHT / 2;
// 	vis->oper_sz.x = SCREEN_WIDTH / 2;
// }

void			background(t_vis *vis, t_lem_in *li)
{
	li = 0;  //!delete
	vis->bgrnd_clr = get_color(CLR_BG);
	vis->rect_clr = get_color(CLR_RECT);
	vis->text_clr = get_color(CLR_TEXT);
	// rect_size(vis, chkr);
	// text(vis);
}
