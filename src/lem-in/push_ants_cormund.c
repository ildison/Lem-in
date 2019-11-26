/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ants_cormund.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:00:59 by cormund           #+#    #+#             */
/*   Updated: 2019/11/26 13:17:15 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ant		*init_ants(int count_ants)
{
	t_ant	*first_ant;
	t_ant	*ant;

	if (!(first_ant = ft_memalloc(sizeof(t_ant))))
		error(LI_ERROR_MALLOC);
	first_ant->number = 1;
	ant = first_ant;
	while (count_ants)
	{
		if (!(ant->next = ft_memalloc(sizeof(t_ant))))
			error(LI_ERROR_MALLOC);
		ant->next->number = ++(ant->number);
		ant = ant->next;
		--count_ants;
	}
	ant = NULL;
	return (first_ant);
}

void		move_ant(t_ant *ant, t_path *path)
{
	// if (ant->end)
	// 	return ;
	if (ant->move && (*ant->room)->type == LI_END)
	{
		(*ant->room)->vizited = false;
		ant->end = true;
		++(*ant->room)->count_ants;
	}
	else if (ant->move && (*ant->room + 1)->vizited)
		return ;
	else if (ant->move)
	{
		(*ant->room)->vizited = false;
		++ant->room;
		(*ant->room)->vizited = true;
	}
	else
	{
		while (path && (path->vrtx[0]->vizited || !path->ants))
			path = path->next;
		if (!path)
			return ;
		ant->room = path->vrtx;
		ant->move = true;
		(*path->vrtx)->vizited = true;
		--path->ants;
	}
	if (ant->move && !ant->end)
		ft_printf("L%d-%s ", ant->number, (*ant->room)->name);
}

void		push_ants(t_lem_in *li, t_paths paths)
{
	t_ant	*first_ant;
	t_ant	*ant;

	first_ant = init_ants(li->count_ants);
	li->end = li->list_adj[li->count_vertexs - 1];
	// printf("Here\n");
	while (li->end->count_ants < li->count_ants)
	{
		ant = first_ant;
		while (ant)
		{
			if (ant->end)
			{
				ant = ant->next;
				continue ;
			}
			move_ant(ant, paths.path);
			ant = ant->next;
		}
		ft_printf("\n");
	}
}
