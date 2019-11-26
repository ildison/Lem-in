/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 19:34:05 by vmormont          #+#    #+#             */
/*   Updated: 2019/11/25 19:47:11 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			free_input(t_input *input)
{
	t_input		*tmp;
	t_input		*tmp2;

	tmp = input;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp->line);
		free(tmp2);
	}
}

void			free_vertex(t_vertex *vertex)
{
	
}

void			free_lem_in(t_lem_in **li)
{
	if (li)
	{
		free_input((*li)->first_line);
		free_vertex((*li)->start);
		free_vertex((*li)->end);
	}
}