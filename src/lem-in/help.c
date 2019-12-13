/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:15:03 by cormund           #+#    #+#             */
/*   Updated: 2019/12/13 15:23:19 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_help(void)
{
	ft_printf("Welcome to Lem-in (Authors: Cormund and Vmormont)\n\n");
	ft_printf("Start the program correctly:\n\n");
	ft_printf("\t./lem-in {flag} < {map}\n\n");
	ft_printf("Flags:\n\n");
	ft_printf("\t-d - for debug information\n");
	ft_printf("\t-v - for visualisation\n\n");
	ft_printf("Have a nice day, My Friend!\n");
}

void			check_split(char **split)
{
	int			i;

	i = 0;
	while (split[i])
		i++;
	if (i == 2)
		return ;
	error("no valid link");
}
