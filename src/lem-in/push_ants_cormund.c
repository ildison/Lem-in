/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ants_cormund.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:00:59 by cormund           #+#    #+#             */
/*   Updated: 2019/12/02 09:54:21 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ant		*init_ants(int count_ants)
{
	t_ant	*first_ant;
	t_ant	*ant;

	first_ant = ft_memalloc(sizeof(t_ant));
	if (!first_ant)
		error(strerror(errno));
	first_ant->number = 1;
	ant = first_ant;
	while (--count_ants)
	{
		ant->next = ft_memalloc(sizeof(t_ant));
		if (!ant->next)
			error(strerror(errno));
		ant->next->number = ant->number + 1;
		ant = ant->next;
	}
	return (first_ant);
}

// void		move_ant(t_ant *ant, t_path *path)
// {
// 	if (ant->move && (*ant->room)->type == LI_END && (ant->end = true))
// 	{
// 		(*ant->room)->vizited = false;
// 		++(*ant->room)->count_ants;
// 	}
// 	else if (ant->move && (*ant->room + 1)->vizited)
// 		return ;
// 	else if (ant->move)
// 	{
// 		(*ant->room)->vizited = false;
// 		++ant->room;
// 		(*ant->room)->vizited = true;
// 	}
// 	else
// 	{
// 		while (path && (path->vrtx[0]->vizited || !path->ants))
// 			if (!(path = path->next))
// 				return ;
// 		ant->room = path->vrtx;
// 		ant->move = true;
// 		(*path->vrtx)->vizited = true;
// 		--path->ants;
// 	}
// 	if (ant->move && !ant->end)
// 		ft_printf("L%d-%s ", ant->number, (*ant->room)->name);
// }

void		move_ant(t_ant *ant, t_path *path)
{
	if (ant->move && (*ant->room)->type == LI_END)
	{
		ant->move = false;
		ant->end = true;
		(*ant->room)->vizited = false;
	}
	else if (!ant->move)
	{
		while (path && (path->vrtx[0]->vizited || !path->ants))
			path = path->next;
		if (!path)
			return ;
		ant->room = path->vrtx;
		ant->move = true;
		(*path->vrtx)->vizited = true;
		--path->ants;
		if ((*path->vrtx)->type == LI_END)
			++(*path->vrtx)->count_ants;
	}
	else if (ant->move)
	{
		(*ant->room)->vizited = false;
		++ant->room;
		(*ant->room)->vizited = true;
		if ((*ant->room)->type == LI_END)
			++(*ant->room)->count_ants;
	}
	if (ant->move)
		ft_printf("L%d-%s ", ant->number, (*ant->room)->name);
}

void		push_ants(t_lem_in *li, t_paths paths)
{
	t_ant	*first_ant;
	t_ant	*ant;

	first_ant = init_ants(li->count_ants);
	li->end = li->list_adj[li->count_vertex - 1];
	while (li->end->count_ants < li->count_ants)
	{
		ant = first_ant;
		while (ant)
		{
			if (!ant->end)
				move_ant(ant, paths.path);
			ant = ant->next;
		}
		ft_printf("\n");
	}
	// printf("count_step = %d\n", paths.count_steps);
}
