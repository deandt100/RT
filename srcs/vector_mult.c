/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 09:26:08 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/21 09:32:16 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vector	vector_mult(t_vector v1, t_vector v2)
{
	return (t_vector){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}
