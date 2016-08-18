/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 21:06:32 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/18 16:54:08 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

double	vector_dist(t_vector *v1, t_vector *v2)
{
	double		dist;
	t_vector	d;

	d = vector_sub(*v2, *v1);
	dist = SQR(d.x) + SQR(d.y) + SQR(d.z);
	return (sqrtf(dist));
}
