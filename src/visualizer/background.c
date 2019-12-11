/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:33:51 by cormund           #+#    #+#             */
/*   Updated: 2019/12/11 10:59:28 by cormund          ###   ########.fr       */
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

SDL_Color			get_color(int clr)
{
	SDL_Color		color;

	color.r = clr >> 16;
	color.g = (clr >> 8) & 0xff;
	color.b = clr & 0xff;
	color.a = 0xff;
	return (color);
}

static void		set_colors(SDL_Color *colors)
{
	colors[0] = get_color(CLR_1);
	colors[1] = get_color(CLR_2);
	colors[2] = get_color(CLR_3);
	colors[3] = get_color(CLR_4);
	colors[4] = get_color(CLR_5);
	colors[5] = get_color(CLR_6);
	colors[6] = get_color(CLR_7);
	colors[7] = get_color(CLR_8);
	colors[8] = get_color(CLR_9);
	colors[9] = get_color(CLR_10);
	colors[10] = get_color(CLR_11);
	colors[11] = get_color(CLR_12);
	colors[12] = get_color(CLR_13);
	colors[13] = get_color(CLR_14);
	colors[14] = get_color(CLR_15);
	colors[15] = get_color(CLR_16);
	colors[16] = get_color(CLR_17);
}

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

static void		set_new_vrx_coord(t_vertex *v, int indent)
{
	SDL_Point	sq;

	sq.x = SCREEN_WIDTH - indent;
	sq.y = SCREEN_HEIGHT - indent;
	srand(indent);
	while (v)
	{
		if (v->type == LI_START)
		{
			v->coord.x = indent / 2;
			v->coord.y = indent / 2;
		}
		else if (v->type == LI_END)
		{
			v->coord.x = sq.x + indent / 2;
			v->coord.y = sq.y + indent / 2;
		}
		else
		{
			v->coord.x = rand() % (sq.x - indent) + indent;
			v->coord.y = rand() % (sq.y - indent) + indent;
		}
		v = v->next;
	}
}

static void		set_scale(t_vertex *vrx, int indent)
{
	SDL_Point	scale;
	t_vertex	*v;
	int			max_x;
	int			max_y;

	v = vrx;
	max_x = v->coord.x;
	max_y = v->coord.y;
	while (v->next)
	{
		v = v->next;
		max_x = FT_MAX(v->coord.x, max_x);
		max_y = FT_MAX(v->coord.y, max_y);
	}
	scale.x = (SCREEN_WIDTH - indent * 2) / max_x;
	scale.y = (SCREEN_HEIGHT - indent * 2) / max_y;
	v = vrx;
	if (scale.x == 0 || scale.y == 0)
		set_new_vrx_coord(vrx, indent);
	else
		while (v)
		{
			v->coord.x = v->coord.x * scale.x + indent;
			v->coord.y = v->coord.y * scale.y + indent;
			v = v->next;
		}
}

void			background(t_vis *vis, t_lem_in *li)
{
	vis->bgrnd_clr = get_color(CLR_BG);
	vis->gray_clr = get_color(CLR_CIRCLE);
	vis->radius = FT_MIN(SCREEN_WIDTH, SCREEN_HEIGHT) / (li->count_vertex * 3);
	vis->radius = FT_MAX(2, vis->radius);
	vis->line_width = vis->radius / 2.1;
	vis->line_width = FT_MAX(1, vis->line_width);
	set_scale(li->start, SCREEN_WIDTH / 10);
	set_colors(vis->colors);
}
