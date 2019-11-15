/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:10:51 by vmormont          #+#    #+#             */
/*   Updated: 2019/11/15 18:59:59 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			new_path(t_lem_in *lem_in, t_path **path)
{
	t_vertex	*end;
	t_queue		*last;

	end = lem_in->end;
	last = NULL;
	(*path)->step--;
	while (end)
	{
		if (end && end->duplicate)
			begin_enqueue(&(*path)->list, end->neighbor);
		else
			begin_enqueue(&(*path)->list, end);
		if (end->end == LI_TRUE)
			(*path)->endlist = (*path)->list;
		end = end->neighbor;
		(*path)->step++;
	}
}

int				create_path(t_lem_in *lem_in, t_path **path)
{
	if (!*path)
	{
		if (!(*path = (t_path *)ft_memalloc(sizeof(t_path))))
			error(strerror(errno));
		new_path(lem_in, path);
		(*path)->size = 1;
		
		
	}
	else
	{
		/* code */
	}
	
}
