/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 21:06:32 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/07/08 21:50:28 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

float	vector_dist(t_vector *v1, t_vector *v2)
{
	float		dist;
	t_vector	d;

	d = vector_sub(v2, v1);
	dist = SQR(d.x) + SQR(d.y) + SQR(d.z);
	return (sqrtf(dist));
}
