/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 08:19:55 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/21 10:36:33 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		sh_spheres(t_env *env, t_ray *light_ray, float t)
{
	int	k;

	k = 0;
	while (k < env->obj.num_spheres)
	{
		if (intersect_ray_sphere(light_ray, &OBJ.spheres[k], &t))
			return (1);
		k++;
	}
	return (0);
}

int		sh_tri(t_env *env, t_ray *light_ray, float t)
{
	int			k;
	t_vector	n;

	k = 0;
	while (k < env->obj.num_tri)
	{
		if (intersect_ray_tri(light_ray, &TRI[k], &t, &n))
			return (1);
		k++;
	}
	return (0);
}

int		sh_cylinder(t_env *env, t_ray *light_ray, float t)
{
	int			k;

	k = 0;
	while (k < env->obj.num_tri)
	{
		if (intersect_ray_cylinder(light_ray, &CYLINDERS[k], &t))
			return (1);
		k++;
	}
	return (0);
}

int		sh_cone(t_env *env, t_ray *light_ray, float t)
{
	int			k;

	k = 0;
	while (k < env->obj.num_cone)
	{
		if (intersect_ray_cone(light_ray, &CONES[k], &t))
			return (1);
		k++;
	}
	return (0);
}
