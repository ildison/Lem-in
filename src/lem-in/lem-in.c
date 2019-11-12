/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:15:57 by cormund           #+#    #+#             */
/*   Updated: 2019/11/08 13:17:51 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_input(t_input *in)
{
	while (in)
	{
		ft_putendl(in->line);
		in = in->next;
	}
}

int   			main()
{
	t_lem_in	*li;

	li = (t_lem_in *)ft_memalloc(sizeof(t_lem_in));
	if (!li)
		error(strerror(errno));
	read_input(&li->first_line);
	print_input(li->first_line);
	parsing(li);
	return (0);
}
