/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_structs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 12:24:33 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/07/08 18:44:04 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	print_vector(char *des, t_vector v)
{
	printf("%s (%f ; %f ; %f)\n", des, v.x, v.y, v.z);
}

void	set_col(t_col *col, float r, float g, float b)
{
	col->r = r;
	col->g = g;
	col->b = b;
}
