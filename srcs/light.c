/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 08:19:55 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/22 14:11:22 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

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
	t_vector	dir;
	double		temp;
	double		term;

	lam = vector_dot(light_ray.dir, OBJ.normal) * coef;
	dir = vector_sub(light_ray.dir, env->ray.dir);
	temp = sqrt(vector_dot(dir, dir));
	dir = vector_scale(1.0 / temp, dir);
	term = vector_dot(dir, OBJ.normal);
	term = (term > 0.0f) ? term : 0.0f;
	spec = powf(term, 50) * env->spec_coef;

	OBJ.col.r += lam * light.intensity.r * OBJ.cur_mat.diffuse.r;
	OBJ.col.g += lam * light.intensity.g * OBJ.cur_mat.diffuse.g;
	OBJ.col.b += lam * light.intensity.b * OBJ.cur_mat.diffuse.b;

	OBJ.col.r += spec * light.intensity.r * OBJ.cur_mat.diffuse.r;
	OBJ.col.g += spec * light.intensity.g * OBJ.cur_mat.diffuse.g;
	OBJ.col.b += spec * light.intensity.b * OBJ.cur_mat.diffuse.b;
}

void	add_global(t_env *env, t_light *light)
{
	OBJ.col.r += (0.2 * env->ambient_coef) * light->intensity.r * OBJ.cur_mat.diffuse.r;
	OBJ.col.g += (0.2 * env->ambient_coef) * light->intensity.g * OBJ.cur_mat.diffuse.g;
	OBJ.col.b += (0.2 * env->ambient_coef) * light->intensity.b * OBJ.cur_mat.diffuse.b;
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
		add_global(env, &OBJ.lights[j]);
		if (vector_dot(OBJ.normal, dist) <= 0.0F)
		{
			j++;
			continue ;
		}
		t = sqrt(vector_dot(dist, dist));
		if (t <= 0.00001f)
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
