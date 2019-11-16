/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:41:25 by cormund           #+#    #+#             */
/*   Updated: 2019/11/17 01:26:31 by vmormont         ###   ########.fr       */
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

typedef struct s_input		t_input;
typedef struct s_pnt		t_pnt;
typedef struct s_vertex		t_vertex;
typedef struct s_link		t_link;
typedef struct s_link_adj	t_link_adj;
typedef struct s_lem_in		t_lem_in;
typedef struct s_queue		t_queue;
typedef struct s_path		t_path;

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
	t_pnt					coord;
	char					*name;
	char					start;
	char					end;
	int						id;
	int						dist;
	bool					marked;
	bool					visited;
	bool					duplicate;
	t_queue					*vertex_link;
	t_link					*link;
	struct s_vertex			*neighbor;
	struct s_vertex			*next;
};

struct						s_link
{
	t_vertex				*vertex_a;
	t_vertex				*vertex_b;
	bool					block;
	int						weight;
	struct s_link			*next;
};

struct						s_link_adj
{
	t_vertex				*vertex;
	t_vertex				**adj;
	int						count_edges;
};

struct						s_lem_in
{
	t_input					*first_line;
	t_vertex				*start;
	t_vertex				*end;
	t_link					*first_link;
	t_vertex				**hash_table;
	t_link_adj				*link_adj;
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

void						enqueue(t_queue **queue, t_vertex *vertex, t_queue **last);
void						begin_enqueue(t_queue **queue, t_vertex *vertex);
void						pop_queue(t_queue **queue);
int							calc_dist(t_queue *queue, t_link_adj *link_adj, t_queue *last);

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

int							bfs(t_lem_in *lem_in, t_path **path);

void						vertex_links(t_path *path);

void						read_input(t_input **beg_input);
void						parsing(t_lem_in *li);
void 						adjacencies(t_lem_in *li);

# endif