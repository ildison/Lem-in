/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:23:55 by cormund           #+#    #+#             */
/*   Updated: 2019/12/04 20:39:28 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_vertex	*new_vertex(char *line, int vertex_type)
{
	t_vertex	*vertex;
	char		**split_line;

	split_line = ft_strsplit(line, ' ');
	vertex = (t_vertex *)ft_memalloc(sizeof(t_vertex));
	if (!vertex || !split_line)
		error(strerror(errno));
	vertex->name = ft_strdup(split_line[0]);
	vertex->coord.x = ft_atoi(split_line[1]);
	vertex->coord.y = ft_atoi(split_line[2]);
	ft_free_2x_mas((void **)split_line);
	vertex->type = vertex_type;
	return (vertex);
}

static void		add_vertex(t_vertex **start, t_vertex *vertex)
{
	t_vertex	*tmp;

	if (!(tmp = *start))
		*start = vertex;
	else
	{
		if (vertex->type == LI_VERTEX || vertex->type == LI_END)
		{
			while (tmp->next && tmp->next->type != LI_END)
				tmp = tmp->next;
			if (!tmp->next)
				tmp->next = vertex;
			else
			{
				vertex->next = tmp->next;
				tmp->next = vertex;
			}
		}
		else if (vertex->type == LI_START)
		{
			vertex->next = tmp;
			*start = vertex;
		}
	}
}

static t_vertex	*get_vertex(t_vertex *vertex, char *name)
{
	while (vertex && !ft_strequ(vertex->name, name))
	{
		vertex = vertex->next;
		while (vertex && *vertex->name != *name)
			vertex = vertex->next;
	}
	return (vertex);
}

static void		add_new_link(t_link **first_link, t_vertex *vertex, char *line)
{
	t_link		*link;
	char		**split_line;

	split_line = ft_strsplit(line, '-');
	link = (t_link *)ft_memalloc(sizeof(t_link));
	if (!link || !split_line)
		error(strerror(errno));
	link->vertex_a = get_vertex(vertex, split_line[0]);
	link->vertex_b = get_vertex(vertex, split_line[1]);
	ft_free_2x_mas((void **)split_line);
	if (*first_link)
		link->next = *first_link;
	*first_link = link;
}

void			parsing(t_lem_in *li)
{
	t_input		*input;
	t_vertex	*vertex;

	if ((input = li->first_line->next))
		while (input->line)
		{
			if (input->type == LI_START || input->type == LI_END)
			{
				vertex = new_vertex(input->next->line, input->type);
				add_vertex(&li->start, vertex);
				input = input->next;
			}
			else if (input->type == LI_VERTEX)
			{
				vertex = new_vertex(input->line, LI_VERTEX);
				add_vertex(&li->start, vertex);
			}
			else if (input->type == LI_LINK)
			{
				add_new_link(&li->first_link, li->start, input->line);
				li->flag_link = true;
			}
			input = input->next;
		}
	li->count_ants = validation(li, li->first_line->line);
}
