/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:54:03 by vmormont          #+#    #+#             */
/*   Updated: 2019/11/14 21:27:11 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define COUNT_START lem_in->link_adj[0].vertex->count_edges
#define COUNT_END lem_in->link_adj[end - 1].vertex->count_edges



int				bfs(t_lem_in *lem_in, ...)
{
	int			end;
	t_queue		*queue;
	t_queue		*last;
	
	last = lem_in->count_vertexs;
	queue = NULL;
	last = NULL;
	lem_in->count_path = COUNT_START < COUNT_END ? COUNT_START : COUNT_END;
	enqueu();
}
