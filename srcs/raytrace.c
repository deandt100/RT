/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddu-toit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 07:24:50 by ddu-toit          #+#    #+#             */
/*   Updated: 2016/08/18 12:20:29 by ddu-toit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

/*
** Reflect ray around normal.
*/

static void			reflect_ray(t_env *env, t_ray *ray)
{
	float		reflect;
	t_vector	tmp;

	ray->start = OBJ.new_start;
	reflect = 2.0f * vector_dot(&ray->dir, &OBJ.normal);
	tmp = vector_scale(reflect, &OBJ.normal);
	ray->dir = vector_sub(&ray->dir, &tmp);
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
	while (coef > 0.0f && level_max--)
	{
		t = 20000.0f;
		get_intersections(env, ray, &t);
		if (OBJ.cur_sphere != -1)
			set_val_sphere(env, t, ray);
		else if (OBJ.cur_tri != -1)
			set_val_tri(env, t, ray);
		else if (OBJ.cur_cyl != -1)
		{
			set_val_cyl(env, t, ray);
//			set_col(&OBJ.col, 42, 42, 42);
//			return(OBJ.col);
		}
		else if (OBJ.cur_cone != -1)
		{
			set_val_cone(env, t, ray);
		}
		else
			break ;
		if (env->br == 1)
			break ;
		calc_lighting(env, coef);
		coef *= OBJ.cur_mat.reflection;
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
	t_vector	ut;
	t_vector	vt;

	ut = vector_scale(x * CAM.w / (double)WIN_X, &CAM.u);
	vt = vector_scale(y * CAM.h / (double)WIN_Y, &CAM.v);
	s = vector_add(&CAM.l, &ut);
	s = vector_sub(&s, &vt);
//	print_vector("u : ", CAM.u);
//	print_vector("ut : ", ut);
//	print_vector("s : ", s);
	ray->dir = vector_sub(&s, &CAM.pos);
//	ray->dir = vector_unit(ray->dir);
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
	t_col	col;

	y = 0;
	ray.start = CAM.pos;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
//			ray.start.x += x;
//			ray.start.y += y;
			create_ray(x, y, &ray, env);
//			print_vector("cam s: ", ray.start);
//			print_vector("cam d: ", ray.dir);
//:			ray.dir = OBJ.cam_dir;
//			vector_norm(&ray.dir);
			set_col(&OBJ.col, 0, 0, 0);
			env->br = 0;
			col = shoot_ray(ray, 5, env);
			save_to_img(env, col, x, y);
			x++;
		}
		y++;
	}
}
