/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:41:25 by cormund           #+#    #+#             */
/*   Updated: 2019/11/14 21:24:02 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdbool.h>

# define LI_STDIN 0

# define LI_TRUE 1
# define LI_FALSE 0

# define LI_START 1
# define LI_END 2
# define LI_COMMENT 3
# define LI_VERTEX 4
# define LI_LINK 5

# define CH_START '1'
# define CH_END '0'

typedef struct		s_input t_input;
typedef struct		s_pnt t_pnt;
typedef struct		s_vertex t_vertex;
typedef struct		s_link t_link;



typedef struct		s_input
{
	char			*line;
	int				type;
	struct s_input	*next;
}					t_input;

typedef struct		s_pnt
{
	int				y;
	int				x;
}					t_pnt;

typedef struct		s_vertex
{
	char			*name;
	int				id;
	bool			visited;
	t_pnt			coord;
	char			start;
	char			end;
	int				count_edges;
	// t_link			*links;
	struct s_vertex	*next;
}					t_vertex;

typedef struct		s_link
{
	t_vertex		*vertex_a;
	t_vertex		*vertex_b;
	bool			block;
	struct s_link	*next;
}					t_link;

typedef struct		s_link_adj
{
	t_vertex		*vertex;
	t_vertex		**adj;
}					t_link_adj;

typedef struct		s_lem_in
{
	t_input			*first_line;
	t_vertex		*start;
	t_link			*first_link;
	t_vertex		**hash_table;
	t_link_adj		*link_adj;
	char			**matrix_adj;
	int				count_ants;
	int				count_vertexs;
	int				count_path;
}					t_lem_in;

typedef struct		s_queue
{
	int						index;
	int						steps;
	t_vertex				*vertex;
	t_queue					*next;
	t_queue					*prev;
}					t_queue;


void				read_input(t_input **beg_input);
void				parsing(t_lem_in *li);
void 				adjacencies(t_lem_in *li);

# endif