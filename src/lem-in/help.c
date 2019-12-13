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
	ft_printf("Welcome to Lem-in (Authors: Cormund and Vmormont\n");
	ft_printf("Start the program correctly:\n");
	ft_printf("\t./lem-in {flag} < {map}\n");
	ft_printf("Flags:\n");
	ft_printf("\t-d - for debug information\n");
	ft_printf("\t-v - for visualisation\n");
	ft_printf("Have a nica day, My Friend!\n");
}
