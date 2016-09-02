/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refract_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oexall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/02 13:38:55 by oexall            #+#    #+#             */
/*   Updated: 2016/09/02 15:20:40 by oexall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_ray	ft_refract_ray(t_env *env, t_ray ray1)
{
	t_ray	ray2;
	double	c1;
	double	c2;
	double	n;

	env->in_obj = 1;
	OBJ.normal = vector_sub((t_vector){0, 0, 0}, OBJ.normal);
	c1 = -(vector_dot(OBJ.normal, ray1.dir));
	n = 5 / OBJ.cur_mat.refraction;
	c2 = sqrt(1 - (n * 2) * (1 - (c1 * 2)));
	ray2.start = ray1.start;
	ray2.dir = vector_add(
			vector_scale(n, ray1.dir),
			vector_scale((n * c1 - c2), OBJ.normal));
	ray2.dir = vector_scale(n, ray1.dir);
	return (ray2);
}
