/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:37:03 by cormund           #+#    #+#             */
/*   Updated: 2019/11/08 15:40:46 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		read_input(t_input **first_input)
{
	t_input	*input;

	*first_input = (t_input *)ft_memalloc(sizeof(t_input));
	if (!*first_input)
		error(strerror(errno));
	input = *first_input;
	while ((input->line = gnl(LI_STDIN)))
	{
		input->next = (t_input *)ft_memalloc(sizeof(t_input));
		if (!input->next)
			error(strerror(errno));
		input = input->next;
	}
}
