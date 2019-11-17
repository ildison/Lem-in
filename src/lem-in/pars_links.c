/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 01:22:17 by cormund           #+#    #+#             */
/*   Updated: 2019/11/18 01:22:59 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_link				*make_link(t_vertex *v1, char *n2)
{
	t_link			*new;
	t_link			*old;
	
	if (v1->links)
	{
		old = v1->links;
		while (old)
		{
			if (!(ft_strequ(old->vertex->name, n2)))
				return (v1->links);
			old = old->next;
		}
		if (!(new = (t_link *)ft_memalloc(sizeof(t_link))))
			error(strerror(errno));
		new->next = v1->links;
		v1->links = new;
	}
	else if (!(v1->links = (t_link *)ft_memalloc(sizeof(t_link))))
		error(strerror(errno));
	v1->links->weight = 1;
	return (v1->links);
}

void				link_vertexs(t_vertex *v1, t_vertex *v2)
{
	v1->links = make_link(v1, v2->name);
	v2->links = make_link(v2, v1->name);
	v1->links->vertex = v2;
	v2->links->vertex = v1;
}

int				add_new_link(char *n1, char *n2,  t_hash_table *hash_table, int count_vertexs)
{
	t_vertex	*v1;
	t_vertex	*v2;
	int			code1;
	int			code2;
	
	code1 = hash(n1, count_vertexs);
	code2 = hash(n2, count_vertexs);
	if (code1 == code2)
	{
		v1 = hash_table[code1].vertex;
		v2 = hash_table[code2].vertex;
		while (v1 && ft_strequ(v1->name, n1))
			v1 = v1->next;
		while (v2 && ft_strequ(v2->name, n2))
			v2 = v2->next;
		if (!v1 || !v2 || v1 == v2)
			return (ERROR_LINK);
		link_vertexs(v1, v2);
		return (1);
	}
	else if (!(v1 = get_vertex(n2, hash_table, count_vertexs) || !(v2 = get_vertex(n1, hash_table, count_vertexs))))
		return (ERROR_LINK);
	link_vertexs(v1, v2);
	return (LI_LINK);
}
