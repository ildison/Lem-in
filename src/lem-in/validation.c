/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 02:27:47 by vmormont          #+#    #+#             */
/*   Updated: 2019/11/18 01:53:57 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		valid_vertexs(t_input **input)
{
	int			vertexs;
	int			error;

	vertexs = 0;
	error = 0;
	while ((*input) && (*input)->type != LI_LINK)
	{
		if ((*input)->type == LI_VERTEX)
			++vertexs;
		else if ((*input)->type == LI_START || (*input)->type == LI_END)
		{
			if (!((*input) = (*input)->next) && ((*input)->type != LI_VERTEX))
				error(strerror(errno));
			(*input)->type = (*input)->back->type;
			(*input)->back->type = LI_COMMENT;
			error = error + (*input)->type;
			++vertexs;
		}
		else if ((*input)->type != LI_COMMENT)
			error(strerror(errno));
		(*input) = (*input)->next;
	}
	if (error != (LI_START + LI_END) || vertexs < 2)
		error(strerror(errno));
	return (vertexs);
}


int             get_links(t_lem_in *lem_in, int count_vertexs)
{
    lem_in->hash_table = hash_table(lem_in->start, count_vertexs);
    
}

int             validation(t_lem_in *lem_in)
{
    if (!(lem_in->count_vertexs = valid_vertexs(&lem_in->input))
        || !get_links(lem_in, lem_in->count_vertexs)
        || !valid_links()
        || !breadth_search(lem_in, &lem_in->paths))
        return (free_lem_in(&lem_in));
    return (1);
}
