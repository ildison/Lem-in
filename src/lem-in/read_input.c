/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:37:03 by cormund           #+#    #+#             */
/*   Updated: 2019/11/12 16:03:09 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	1 - start, 2 - end, 3 - comment, 4 - vertex, 5 - edges, 6 - ants or trash
*/

int             check_line(char *line)
{
    if (*line == '#')
    {
       if (ft_strequ(line, "##start"))
			return (1);
		if (ft_strequ(line, "##end"))
			return (2);
		return (3);
    }
	while (*line)
	{
		if (*line == ' ')
			return (4);
		if (*line == '-')
			return (5);
		++line;
	}
	return (6);
}

void		read_input(t_input **first_input)
{
	t_input	*input;

	*first_input = (t_input *)ft_memalloc(sizeof(t_input));
	if (!*first_input)
		error(strerror(errno));
	input = *first_input;
	while ((input->line = gnl(LI_STDIN)))
	{
		input->type = check_line(input->line);
		input->next = (t_input *)ft_memalloc(sizeof(t_input));
		if (!input->next)
			error(strerror(errno));
		input = input->next;
	}
}
