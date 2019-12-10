/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_step.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <cormund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:50:51 by cormund           #+#    #+#             */
/*   Updated: 2019/12/10 12:24:46 by cormund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "li_visualizer.h"

t_step	*next_step(t_step *step)
{
	if (step && step->next && !step->fin)
		return (step->next);
	return (step);
}