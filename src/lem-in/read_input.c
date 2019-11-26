/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:37:03 by cormund           #+#    #+#             */
/*   Updated: 2019/11/26 13:28:40 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int             check_line(char *line)
{
    if (*line == '#')
    {
       if (ft_strequ(line, "##start"))
			return (LI_START);
		if (ft_strequ(line, "##end"))
			return (LI_END);
		return (LI_COMMENT);
    }
	while (*line)
	{
		if (*line == ' ')
			return (LI_VERTEX);
		if (*line == '-')
			return (LI_LINK);
		++line;
	}
	return (6);
}

void		read_input(t_input **first_input)
{
	t_input	*input;

	if (!(*first_input = (t_input *)ft_memalloc(sizeof(t_input))))
		error(LI_ERROR_MALLOC);
	input = *first_input;
	while ((input->line = gnl(LI_STDIN)))
	{
		input->type = check_line(input->line);
		if (!(input->next = (t_input *)ft_memalloc(sizeof(t_input))))
			error(LI_ERROR_MALLOC);
		input = input->next;
	}
}
