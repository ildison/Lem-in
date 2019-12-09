/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_visualizer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:03:24 by cormund           #+#    #+#             */
/*   Updated: 2019/12/09 13:01:14 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_VISUALIZER_H
# define PS_VISUALIZER_H

# include "lem_in.h"
# include "SDL.h"
# include "SDL_ttf.h"
# include "SDL2_framerate.h"
# include "SDL2_gfxPrimitives.h"
# include "SDL2_imageFilter.h"
# include "SDL2_rotozoom.h"

# define SCREEN_WIDTH 2040
# define SCREEN_HEIGHT 1240

# define SDL_EVENT vis->e.type
# define SDL_KEYSTATE vis->keystate
# define SDL_ESCAPE SDL_SCANCODE_ESCAPE
# define SDL_SPACE SDL_SCANCODE_SPACE
# define SDL_RIGHT SDL_SCANCODE_RIGHT
# define SDL_LEFT SDL_SCANCODE_LEFT
# define SDL_UP SDL_SCANCODE_UP
# define SDL_DOWN SDL_SCANCODE_DOWN
# define SDL_R SDL_SCANCODE_R

# define FIRST_STEP "begin"

# define CLR_TEXT 0xddd9c9
# define CLR_BG 0x414244
# define CLR_RECT 0xddd9c9

typedef struct		s_step
{
	SDL_Texture		*oper;
	SDL_Rect		oper_rect;
	SDL_bool		fin;
	struct s_step	*prev;
	struct s_step	*next;
}					t_step;

typedef struct		s_vis
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	TTF_Font		*font_text;
	SDL_Color		text_clr;
	SDL_Color		bgrnd_clr;
	SDL_Color		rect_clr;
	SDL_Point		scale;
	SDL_Event		e;
	SDL_bool		quit;
	SDL_bool		pause;
	t_step			*first_step;
	t_pnt			rect;
	int				radius;
	int				line_width;
	int				delay;
	const Uint8		*keystate;
	int				between_rect;
}					t_vis;

void				background(t_vis *vis, t_lem_in *li);
void				loop(t_vis *vis, t_lem_in *li);
// void				render_texts(t_vis *vis, t_step *stp);
// void				render_rects(t_vis *vis, t_step *stp);
// t_step				*new_step(t_checker *chkr, t_vis *vis, char *oper);
// t_step				*next_step(t_vis *vis, t_step *step, t_checker *chkr);
// SDL_Texture			*create_texture(TTF_Font *font, char *text,\
// 										SDL_Renderer *ren, SDL_Color color);

#endif