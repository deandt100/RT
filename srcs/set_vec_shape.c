/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vec_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 07:24:50 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/15 15:56:40 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

/*
** Mostly norm functions to set new_start an normal for shapes.
*/

void	set_val_sphere(t_env *env, float t, t_ray ray)
{
	t_vector	scaled;

	scaled = vector_scale(t, &ray.dir);
	OBJ.new_start = vector_add(&ray.start, &scaled);
	OBJ.normal = vector_sub(&OBJ.new_start, &SP_POS(OBJ.cur_sphere));
	if (vector_dot(&OBJ.normal, &OBJ.normal) == 0)
	{
		env->br = 1;
		return ;
	}
	OBJ.normal = vector_scale(1.0f / ABSV(OBJ.normal), &OBJ.normal);
	OBJ.cur_mat = env->obj.mats[SPHERES[OBJ.cur_sphere].shape.material];
}

void	set_val_tri(t_env *env, float t, t_ray ray)
{
	t_vector	scaled;

	scaled = vector_scale(t, &ray.dir);
	OBJ.new_start = vector_add(&ray.start, &scaled);
	OBJ.normal = TRI[OBJ.cur_tri].normal;
	if (vector_dot(&OBJ.normal, &OBJ.normal) == 0)
	{
		env->br = 1;
		return ;
	}
	OBJ.normal = vector_scale(1.0f / ABSV(OBJ.normal), &OBJ.normal);
	OBJ.cur_mat = env->obj.mats[TRI[OBJ.cur_tri].shape.material];
}

void	unrotate_vec(t_env *env, int i, t_vector *vec)
{
	rotate_vec_x(-CYLINDERS[i].rot.x, vec);
	rotate_vec_y(-CYLINDERS[i].rot.y, vec);
	rotate_vec_z(-CYLINDERS[i].rot.z, vec);
}

void	set_val_cyl(t_env *env, float t, t_ray ray)
{
	t_vector	scaled;

	scaled = vector_scale(t, &ray.dir);
	OBJ.new_start = vector_add(&ray.start, &scaled);
	OBJ.normal = vector_sub(&OBJ.new_start, &CYL_POS(OBJ.cur_cyl));
	unrotate_vec(env, OBJ.cur_cyl, &OBJ.normal);
	OBJ.normal.y = 0;
	rotate_vec_x(CYLINDERS[OBJ.cur_cyl].rot.x, &OBJ.normal);
	rotate_vec_y(CYLINDERS[OBJ.cur_cyl].rot.y, &OBJ.normal);
	rotate_vec_z(CYLINDERS[OBJ.cur_cyl].rot.z, &OBJ.normal);
	if (vector_dot(&OBJ.normal, &OBJ.normal) == 0)
	{
		env->br = 1;
		return ;
	}
	OBJ.normal = vector_scale(1.0f / ABSV(OBJ.normal), &OBJ.normal);
	vector_norm(&OBJ.normal);
	OBJ.cur_mat = env->obj.mats[CYLINDERS[OBJ.cur_cyl].shape.material];
}

void	set_val_cone(t_env *env, float t, t_ray ray)
{
	t_vector	scaled;

	scaled = vector_scale(t, &ray.dir);
	OBJ.new_start = vector_add(&ray.start, &scaled);
	OBJ.normal = vector_sub(&OBJ.new_start, &CN_POS(OBJ.cur_cone));
	unrotate_vec2(env, OBJ.cur_cone, &OBJ.normal);
	OBJ.normal.y *= -1.0f;
	rotate_vec_x(CONES[OBJ.cur_cone].rot.x, &OBJ.normal);
	rotate_vec_y(CONES[OBJ.cur_cone].rot.y, &OBJ.normal);
	rotate_vec_z(CONES[OBJ.cur_cone].rot.z, &OBJ.normal);
	if (vector_dot(&OBJ.normal, &OBJ.normal) == 0)
	{
		env->br = 1;
		return ;
	}
	OBJ.normal = vector_scale(1.0f / ABSV(OBJ.normal), &OBJ.normal);
	vector_norm(&OBJ.normal);
	OBJ.cur_mat = env->obj.mats[CONES[OBJ.cur_cone].shape.material];
}
