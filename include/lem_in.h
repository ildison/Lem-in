/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:41:25 by cormund           #+#    #+#             */
/*   Updated: 2019/11/22 13:19:29 by cormund          ###   ########.fr       */
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

# define LI_OPEN 0
# define LI_CLOSE 1

typedef struct s_input		t_input;
typedef struct s_pnt		t_pnt;
typedef struct s_vertex		t_vertex;
typedef struct s_link		t_link;
typedef struct s_list_adj	t_list_adj;
typedef struct s_lem_in		t_lem_in;
typedef struct s_queue		t_queue;
typedef struct s_path		t_path;
typedef struct s_paths		t_paths;

struct						s_input
{
	char					*line;
	int						type;
	struct s_input			*next;
};

struct						s_pnt
{
	int						y;
	int						x;
};

struct						s_vertex
{
	t_list_adj				*adj;
	t_pnt					coord;
	int						id;
	int						count_edges;
	int						dist;
	int						adj_index;
	int						path_index;
	char					*name;
	char					type;
	bool					marked;
	bool					splited;
	bool					visited;
	bool					duplicate;
	struct s_vertex			*neighbor;
	struct s_vertex			*next;
};

struct						s_link
{
	t_vertex				*vertex_a;
	t_vertex				*vertex_b;
	struct s_link			*next;
};

struct						s_list_adj
{
	t_vertex				*vrtx;
	bool					status;
	int						index;
};

struct						s_lem_in
{
	t_input					*first_line;
	t_vertex				*start;
	t_vertex				*end;
	t_vertex				**hash_table;
	t_vertex				**list_adj;
	t_link					*first_link;
	t_list_adj				*list_adj_old; //? delete
	char					**matrix_adj;
	int						count_ants;
	int						count_vertexs;
	int						count_path;
};

struct						s_queue
{
	int						index;
	int						steps;
	t_vertex				*vertex;
	t_queue					*next;
	t_queue					*prev;
};

struct						s_path
{
	t_queue					*list;
	t_queue					*endlist;
	t_path					*next;
	int						index;
	int						step;
	int						size;
	bool					checked;
};

struct						s_paths
{
	t_vertex				*vertex;
	t_paths					*next;
};

void						read_input(t_input **beg_input);
void						parsing(t_lem_in *li);
void 						adjacencies(t_lem_in *li);

# endif