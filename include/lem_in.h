/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <vmormont@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:41:25 by cormund           #+#    #+#             */
/*   Updated: 2019/11/18 02:00:44 by vmormont         ###   ########.fr       */
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

# define ERROR_LINK -1

# define CAPACITY 7

typedef struct s_input		t_input;
typedef struct s_pnt		t_pnt;
typedef struct s_vertex		t_vertex;
typedef struct s_link		t_link;
typedef struct s_link_adj	t_link_adj;
typedef struct s_lem_in		t_lem_in;
typedef struct s_queue		t_queue;
typedef struct s_path		t_path;
typedef struct s_hash_table	t_hash_table;
typedef struct s_hash_code	t_hash_code;


/*
**  The following two structures are a special data
** structure for storing key pairs and their values.
*/

struct						s_hash_table
{
	t_vertex				*vertex;
};

struct						s_hash_code
{
	int						code;
	t_hash_code				*next;
};

/*
**  This structure is responsible for saving
**  the read data.
*/

struct						s_input
{
	char					*line;
	int						type;
	t_input					*back;
	t_input					*next;
};

/*
**  This structure is responsible for maintaining
**  the coordinates of the vertices.
*/

struct						s_pnt
{
	int						y;
	int						x;
};

/*
**  This structure is responsible for saving all data
**  for working with the vertex.
*/

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
	t_link					*links;
	struct s_vertex			*neighbor;
	struct s_vertex			*next;
};

/*
**  This structure stores all the links (pointers)
** of this vertex.
*/

struct						s_link
{
	t_vertex				*vertex;
	bool					block;
	int						weight;
	struct s_link			*next;
};

/*
**  This structure stores adjacency sheets
*/

struct						s_link_adj
{
	t_link					*links;
	int						count_edges;
};

/*
**  This structure stores a queue (sequence of vertices)
**  for further processing and searching for paths in a graph.
*/

struct						s_queue
{
	int						index;
	int						steps;
	t_vertex				*vertex;
	t_queue					*next;
	t_queue					*prev;
};

/*
**  This structure stores all the paths in a graph.
*/

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

/*
**  This structure is the main one, it stores all
**  of the above structures.
*/

struct						s_lem_in
{
	t_input					*input;
	t_vertex				*start;
	t_vertex				*end;
	t_link					*links;
	// t_vertex				**hash_table;
	// t_link_adj				*link_adj;
	t_path					*paths;
	t_hash_code				*hash_code;
	t_hash_code				*hash_table;
	char					**matrix_adj;
	int						hash_start;
	int						hash_end;
	int						count_ants;
	int						count_vertexs;
	int						count_path;
	bool					duplicate;
	t_pnt					**pnts;
};

void						read_input(t_input **input);

int							parsing(t_lem_in *li, t_hash_table *hash_table, t_hash_code **hash_code);
int							get_ants(t_input **input);

int							check_start_end(t_lem_in *li, t_hash_table *hash_table, t_hash_code **hash_code, char *line);
int							make_vertex(t_lem_in *li, t_hash_table *hash_table, char **split, char type);
int							hash(char *name, int count_vertexs);
int							add_new_link(char *n1, char *n2,  t_hash_table *hash_table, int count_vertexs);
void						link_vertexs(t_vertex *v1, t_vertex *v2);
t_link						*make_link(t_vertex *v1, char *n2);

int             			validation(t_lem_in *lem_in);

int							breadth_search(t_lem_in *lem_in, t_path **path);
int							count_paths(t_lem_in *li);

void						enqueue(t_queue **queue, t_vertex *vertex, t_queue **last);
void						begin_enqueue(t_queue **queue, t_vertex *vertex);
void						pop_queue(t_queue **queue);
int							calc_dist(t_queue *queue, t_vertex *start, t_queue *last);


# endif