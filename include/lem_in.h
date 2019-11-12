/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:41:25 by cormund           #+#    #+#             */
/*   Updated: 2019/11/12 16:13:04 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define LI_STDIN 0
# define LI_NEXT_LINE ""
# define LI_TRUE 1
# define LI_START 1
# define LI_END 2
# define LI_VERTEX 4
# define LI_LINK 5
# define LI_TRUE 1

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
	t_pnt			coord;
	char			start;
	char			end;
	struct s_vertex	*next;
}					t_vertex;

typedef struct		s_link
{
	t_vertex		*vertex_a;
	t_vertex		*vertex_b;
	struct s_link	*next;
}					t_link;

typedef struct		s_lem_in
{
	t_input			*first_line;
	t_vertex		*start;
	t_link			*first_link;
	int				count_ants;
}					t_lem_in;

void				read_input(t_input **beg_input);
void				parsing(t_lem_in *li);

# endif