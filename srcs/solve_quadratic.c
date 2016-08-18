/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviwel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 23:27:50 by daviwel           #+#    #+#             */
/*   Updated: 2016/08/15 09:49:57 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int	solve_quadratic(t_ray_sphere *rs, float *t)
{
	rs->t0 = (-rs->b - sqrt(rs->discr)) / (2 * rs->a);
	rs->t1 = (-rs->b + sqrt(rs->discr)) / (2 * rs->a);
	if (rs->t0 > rs->t1 && rs->t1 > 0)
		rs->t0 = rs->t1;
	if ((rs->t0 > 0.00001) && (rs->t0 < *t))
	{
		*t = rs->t0;
		return (1);
	}
	else
		return (0);
}
