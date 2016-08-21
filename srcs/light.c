/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 08:19:55 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/21 13:52:59 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		check_in_shadow(t_env *env, float t, t_vector dist, t_ray *light_ray)
{
	int			in_shadow;

	light_ray->start = OBJ.new_start;
	light_ray->dir = vector_unit(vector_scale((1 / t), dist));
	in_shadow = sh_spheres(env, light_ray, t);
	in_shadow += sh_tri(env, light_ray, t);
	in_shadow += sh_cylinder(env, light_ray, t);
	in_shadow += sh_cone(env, light_ray, t);
	return (in_shadow);
}

void	lambert_diffuse(t_env *env, float coef, t_ray light_ray, t_light light)
{
	double		lam;
	double		spec;
	t_vector	r;

	lam = vector_dot(light_ray.dir, OBJ.normal) * coef;
//	print_vector("\nNS", OBJ.new_start);
//	print_vector("L",light.pos);
	r = vector_sub(env->ray.dir,
			        vector_scale(2.0f * vector_dot(env->ray.dir, OBJ.normal), OBJ.normal));
	vector_norm(&r);
	spec = cpow(vector_dot(r, env->ray.dir), OBJ.cur_mat.reflection) * env->spec_coef;
	spec = (spec > 0) ? spec : 0;
//	printf("spec  = %F\n", spec);
	spec = 0;
	OBJ.col.r += (lam + spec) * light.intensity.r * OBJ.cur_mat.diffuse.r;
	OBJ.col.g += (lam + spec) * light.intensity.g * OBJ.cur_mat.diffuse.g;
	OBJ.col.b += (lam + spec) * light.intensity.b * OBJ.cur_mat.diffuse.b;
}

void	calc_lighting(t_env *env, float coef)
{
	int			j;
	t_vector	dist;
	t_ray		light_ray;
	float		t;

	j = 0;
	env->spec_n = 0;
	while (j < OBJ.num_lights)
	{
		dist = vector_sub(OBJ.lights[j].pos, OBJ.new_start);
		if (vector_dot(OBJ.normal, dist) <= 0.0f)
		{
			j++;
			continue ;
		}
		t = sqrt(vector_dot(dist, dist));
		if (t <= 0.0f)
		{
			j++;
			continue ;
		}
		if (check_in_shadow(env, t, dist, &light_ray) == 0)
		{
			lambert_diffuse(env, coef, light_ray, OBJ.lights[j]);
			env->spec_n++;
		}
		j++;
	}
}
