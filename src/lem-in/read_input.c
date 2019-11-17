/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:37:03 by cormund           #+#    #+#             */
/*   Updated: 2019/11/18 01:20:44 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		get_type(char *line)
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

void			read_input(t_input **input)
{
	t_input		*new;
	t_input		*tmp;

	*input = (t_input *)ft_memalloc(sizeof(t_input));
	if (!*input)
		error(strerror(errno));
	new = *input;
	while ((new->line = gnl(LI_STDIN)))
	{
		tmp = new;
		new->type = get_type(new->line);
		if (!(new->next = (t_input *)ft_memalloc(sizeof(t_input))))
			error(strerror(errno));
		new = new->next;
		new->back = tmp;
	}
}
