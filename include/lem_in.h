/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:41:25 by cormund           #+#    #+#             */
/*   Updated: 2019/12/02 11:21:57 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdbool.h>

# define LI_STDIN 0

# define LI_TRUE 1
# define LI_FALSE 0

# define LI_COUNTER -1

# define LI_START 1
# define LI_END 2
# define LI_COMMENT 3
# define LI_VERTEX 4
# define LI_LINK 5

# define CH_START '1'
# define CH_END '0'

# define LI_OPEN 0
# define LI_CLOSE 1

# define LI_ERROR_NO_PATH_FROM_START_TO_END "No path from the start to the end\n"
# define LI_ERROR_NOT_VALID_V "not valid vertexs.\n"
# define LI_ERROR_NOT_VALID_ANTS "not valid count ants.\n"

typedef struct s_input		t_input;
typedef struct s_pnt		t_pnt;
typedef struct s_vertex		t_vertex;
typedef struct s_link		t_link;
typedef struct s_list_adj	t_list_adj;
typedef struct s_lem_in		t_lem_in;
typedef struct s_queue		t_queue;
typedef struct s_path		t_path;
typedef struct s_paths		t_paths;
typedef struct s_ant		t_ant;

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
	bool					duplicate;
	bool					vizited;
	int						count_ants;

	bool					is_in;
	bool					is_out;
	t_vertex				*out;

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
	int						count_vertex;
	int						count_path;
	bool					flag_link;
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
	t_vertex				**vrtx;
	int						dist;
	int						ants;
	t_path					*next;
};

struct						s_paths
{
	t_path					*path;
	int						count_path;
	int						count_steps;
};

struct						s_ant
{
	int						number;
	bool					move;
	bool					end;
	t_vertex				**room;
	t_ant					*next;
};


void						read_input(t_input **beg_input);
void						parsing(t_lem_in *li);
void 						adjacencies(t_lem_in *li);
t_paths						suurballe(t_lem_in *li, int count_required_paths);
void						enqueue(t_queue **queue, t_vertex *vertex,\
														t_queue **last);
t_vertex					*pop_queue(t_queue **queue);
void						clean_queue(t_queue **queue, t_queue **last);
t_vertex					*bfs(t_queue *queue,  t_lem_in *li, t_queue *last);
t_paths						check_paths(t_lem_in *li);

int							validation(t_lem_in *li, char *line);
void						init_dist(int *dist, t_paths finding);
void						push_ants(t_lem_in *li, t_paths paths);
void						print_finding(t_paths finding);
int				is_open_link(t_lem_in *li, t_vertex *src, t_vertex *dst);
void				matrix_adj(char **matrix_adj, t_link *link);

# endif
