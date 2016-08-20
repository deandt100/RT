/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_dot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/04 08:19:55 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/20 14:46:10 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

/*
** Multiply two vectors and return the resulting scalar (dot product)
*/

double	vector_dot(t_vector v1, t_vector v2)
{
	double	dot;

	dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	if (dot <= 0.000001f
		&& dot >= -0.000001f)
		return (0);
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
