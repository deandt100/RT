/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vec_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 07:24:50 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/22 08:06:17 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

/*
** Functions to set new_start and normal for shapes.
*/

void	set_val_sphere(t_env *env, float t, t_ray ray)
{
	OBJ.new_start = vector_add(ray.start, vector_scale(t, ray.dir));
	OBJ.normal = vector_sub(OBJ.new_start, SP_POS(OBJ.cur_sphere));
	if (vector_dot(OBJ.normal, OBJ.normal) == 0)
	{
		env->br = 1;
		return ;
	}
	OBJ.normal = vector_scale(1.0f / ABSV(OBJ.normal), OBJ.normal);
	OBJ.cur_mat = env->obj.mats[SPHERES[OBJ.cur_sphere].shape.material];
}

void	set_val_tri(t_env *env, float t, t_ray ray)
{
	OBJ.new_start = vector_add(ray.start, vector_scale(t, ray.dir));
	OBJ.normal = TRI[OBJ.cur_tri].normal;
	OBJ.normal = vector_scale(1.0f / ABSV(OBJ.normal), OBJ.normal);
	vector_norm(&OBJ.normal);
	if (vector_dot(ray.dir, OBJ.normal) > 0.0F)
		OBJ.normal = vector_sub((t_vector){0.0F, 0.0F, 0.0F}, OBJ.normal);
	OBJ.cur_mat = env->obj.mats[TRI[OBJ.cur_tri].shape.material];
}

void	set_val_cyl(t_env *env, float t, t_ray ray)
{
	t_vector	scaled;

	scaled = vector_scale(t, ray.dir);
	OBJ.new_start = vector_add(ray.start, scaled);
	OBJ.normal = get_cyl_normal(CYLINDERS[OBJ.cur_cyl], OBJ.new_start);
	OBJ.cur_mat = env->obj.mats[CYLINDERS[OBJ.cur_cyl].shape.material];
}

void	set_val_cone(t_env *env, float t, t_ray ray)
{
	OBJ.new_start = vector_add(ray.start, vector_scale(t, ray.dir));
	OBJ.normal = get_cone_normal(CONES[OBJ.cur_cone], OBJ.new_start);
	OBJ.cur_mat = env->obj.mats[CONES[OBJ.cur_cone].shape.material];
	env->spec_coef = OBJ.cur_mat.specular;
}
