/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_ant_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:11:59 by cormund           #+#    #+#             */
/*   Updated: 2019/12/12 12:22:36 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "li_visualizer.h"

void		collect_ant_move(t_vis *vis, t_lem_in *li, t_step *final_step)
{
	t_step	*step;

	step = final_step;
	while (push_ants(li, vis->paths))
	{
		step->next = new_step();
		step->next->prev = step;
		step = step->next;
		step->clr_v = final_step->clr_v;
		step->m_clrs = final_step->m_clrs;
		
	}
}
