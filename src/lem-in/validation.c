/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 02:27:47 by vmormont          #+#    #+#             */
/*   Updated: 2019/11/17 03:15:22 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int             validation(t_lem_in *lem_in)
{
    
}

// static int**	valid_edges(t_input **input)
// {
// 	/*	Need adjacency matrix
// 	**	or adjacency sheets
// 	*/
// }

// static int		valid_vertexs(t_input **input)
// {
// 	int			vertexs;
// 	int			error;

// 	vertexs = 0;
// 	error = 0;
// 	while ((*input) && (*input)->type != 5)
// 	{
// 		if ((*input)->type == 4)
// 			++vertexs;
// 		else if ((*input)->type == 1 || (*input)->type == 2)
// 		{
// 			if (!((*input) = (*input)->front))
// 				put_error("Not valid start/end");
// 			if ((*input)->type == 3)
// 				continue;
// 			if ((*input)->type != 4)
// 				put_error("Not valid start/end");
// 			(*input)->type = (*input)->back->type;
// 			(*input)->back->type = 3;
// 			error = error + (*input)->type;
// 			++vertexs;
// 		}
// 		else if ((*input)->type != 3)
// 			put_error("Not valid vertex");
// 		(*input) = (*input)->front;
// 	}
// 	if (error != 3 || vertexs < 2)
// 		put_error("Not valid vertexs");
// 	return (vertexs);
// }

// static int		valid_ants(t_input **input)
// {
// 	int			ants;

// 	ants = 0;
// 	while ((*input)->type == 3)
// 		(*input) = (*input)->front;
// 	if (!(*input))
// 		put_error("Can't find ants");
// 	ants = ft_atoi((*input)->line);
// 	if (!(ants) || !(ft_strequ((*input)->line, ft_itoa(ants))))
// 		put_error("Not valid ants");
// 	return (ants);
// }

// void			valid_input(t_input	*input, t_lemin *lemin)
// {
// 	lemin->antsNum = valid_ants(&input);
// 	lemin->vertexsNum = valid_vertexs(&input);
// 	lemin->edges = valid_edges(&input); 
// }
