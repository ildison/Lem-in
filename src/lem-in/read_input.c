/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:37:03 by cormund           #+#    #+#             */
/*   Updated: 2019/12/21 14:36:31 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				check_line(char *line)
{
	if (*line == '#')
	{
		if (ft_strequ(line, "##start"))
			return (LI_START);
		if (ft_strequ(line, "##end"))
			return (LI_END);
		return (LI_COMMENT);
	}
	if (*line == ' ' || *line == '\n' || *line == '\0')
		error(LI_ERROR_EMPTY_LINE);
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

void			read_input(t_input **first_input)
{
	t_input		*input;

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
