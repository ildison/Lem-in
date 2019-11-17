/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_vertexs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:23:55 by cormund           #+#    #+#             */
/*   Updated: 2019/11/18 01:24:32 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				hash(char *name, int count_vertexs)
{
	int			count;
	int			code;
	
	count = 0;
	code = 0;
	while (name[count])
	{
		code += name[count];
		++count;
	}
	return (code % (count_vertexs * CAPACITY));
}

int				make_vertex(t_lem_in *li, t_hash_table *hash_table, char **split, char type)
{
	t_vertex	*vertex;
	
	li->hash_start = type == CH_START ? hash(split[0], li->count_vertexs) : li->hash_start;
	li->hash_end = type == CH_END ? hash(split[0], li->count_vertexs) : li->hash_end;
	vertex = type == CH_START ? hash_table[li->hash_start].vertex : hash_table[li->hash_end].vertex;
	vertex->dist = type == CH_START ? 0 : vertex->dist;
	while (vertex)
	{
		if (!(ft_strequ(split[0], vertex->name)))
		{
			li->start = type == CH_START ? vertex : li->start;
			li->end = type == CH_END ? vertex : li->end;
			vertex->start = type == CH_START ? CH_START : vertex->start;
			vertex->end = type == CH_END ? CH_END : vertex->end;
			vertex->coord.x = ft_atoi(split[1]);
			vertex->coord.y = ft_atoi(split[2]);
			return ;
		}
		vertex = vertex->next;
	}
}

int				check_start_end(t_lem_in *li, t_hash_table *hash_table, t_hash_code **hash_code, char *line)
{
	char		type;
	char		**split_line;
	
	if (!(ft_strequ(line, "##start") || !(ft_strequ(line, "##end"))))
		return (0);
	type = ft_strequ(line, "##start") ? CH_START : CH_END;
	split_line = ft_strsplit(line, ' ');
	make_vertex(li, hash_table, split_line, type);
	ft_free_2x_mas(split_line);
	return (1);
}

int				valid_vertexs(t_lem_in *li, t_hash_table *hash_table, t_hash_code **hash_code)
{
	t_vertex	*vertex;
	t_input		*input;
	char		**split;
	
	input = li->input->next;
	if (input)
		while (input->line)
		{
			if (input->type == LI_START || input->type == LI_END)
				if (!(check_start_end(li, hash_table, hash_code, input->line)))
					return (0);
			else if (input->type == LI_VERTEX)
			{
				split = ft_strsplit(input->line, ' ');
				vertex = hash_table[hash(split[0], li->count_vertexs)].vertex;
				vertex->name = ft_strdup(split[0]);
				vertex->coord.x = ft_atoi(split[1]);
				vertex->coord.y = ft_atoi(split[2]);
				ft_free_2x_mas(split);
			}
			else if (input->type == LI_LINK)
			{
				split = ft_strsplit(input->line, '-');
				if (add_new_link(split[0], split[1], hash_table, li->count_vertexs) == ERROR_LINK)
					error(strerror(errno));
				ft_free_2x_mas(split);
			}
			input = input->next;
		}
	else
		error(strerror(errno));
	return (0);
}

int				parsing(t_lem_in *li, t_hash_table *hash_table, t_hash_code **hash_code)
{

	li->count_ants = get_ants(&li->input);
	valid_vertexs(li, hash_table, hash_code);
	make_links(li, hash_table, li->count_vertexs);
	bfs(li, &li->paths);
	return (1);
}
