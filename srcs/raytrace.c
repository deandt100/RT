/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 07:24:50 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/21 13:51:57 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

/*
** Reflect ray around normal.
*/

static void			reflect_ray(t_env *env, t_ray *ray)
{
	ray->start = OBJ.new_start;
	ray->dir = vector_sub(ray->dir,
		vector_scale(2.0f * vector_dot(ray->dir, OBJ.normal), OBJ.normal));
}

/*
** Shoot ray and calculate color value based on reflection, shadows
** and materials.
*/

static t_col		shoot_ray(t_ray ray, int level_max, t_env *env)
{
	float		coef;
	float		t;

	coef = 1.0;
	env->spec_coef = 1;
	while (coef > 0.0f && level_max--)
	{
		t = 20000.0f;
		get_intersections(env, ray, &t);
		if (OBJ.cur_sphere != -1)
			set_val_sphere(env, t, ray);
		else if (OBJ.cur_tri != -1)
			set_val_tri(env, t, ray);
		else if (OBJ.cur_cyl != -1)
			set_val_cyl(env, t, ray);
		else if (OBJ.cur_cone != -1)
			set_val_cone(env, t, ray);
		else
			break ;
		if (env->br == 1)
			break ;
		calc_lighting(env, coef);
		coef *= OBJ.cur_mat.reflection;
		env->spec_coef = 0.0;
		reflect_ray(env, &ray);
	}
	return (OBJ.col);
}

/*
** Save color value to image.
*/

static void			save_to_img(t_env *env, t_col col, int x, int y)
{
	t_col temp;

	if (col.r * 255.0f < 255.0f)
		temp.r = col.r * 255.0f;
	else
		temp.r = 255.0f;
	if (col.g * 255.0f < 255.0f)
		temp.g = col.g * 255.0f;
	else
		temp.g = 255.0f;
	if (col.b * 255.0f < 255.0f)
		temp.b = col.b * 255.0f;
	else
		temp.b = 255.0f;
	env->img.data[(x + y * WIN_X) * 4 + 2] = (unsigned char)temp.r;
	env->img.data[(x + y * WIN_X) * 4 + 1] = (unsigned char)temp.g;
	env->img.data[(x + y * WIN_X) * 4 + 0] = (unsigned char)temp.b;
}

void	create_ray(double x, double y, t_ray *ray, t_env *env)
{
	t_vector	s;

	s = vector_add(CAM.l, vector_scale(x * CAM.w / (double)WIN_X, CAM.u));
	s = vector_sub(s, vector_scale(y * CAM.h / (double)WIN_Y, CAM.v));
	ray->dir = vector_sub(s, CAM.pos);
	vector_norm(&ray->dir);
}

/*
** Iterate through each pixel, shoot ray into scene for each and save returned
** colour value to image.
*/

void				raytrace(t_env *env)
{
	int		x;
	int		y;
	t_ray	ray;

	y = -1;
	ray.start = CAM.pos;
	while (++y < WIN_Y)
	{
		x = -1;
		while (++x < WIN_X)
		{
			create_ray(x, y, &ray, env);
			env->ray = ray;
			OBJ.col = (t_col){0.0, 0.0, 0.0};
			env->br = 0;
			save_to_img(env, shoot_ray(ray, 5, env), x, y);
		}
	}
}
